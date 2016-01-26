#include <ruby.h>
#include <ruby/intern.h>

// This RBASIC_CLASS definition is for Ruby 2.0
#ifndef RBASIC_CLASS
#define RBASIC_CLASS(obj) (RBASIC(obj)->klass)
#endif

struct dig_method {
    VALUE klass;
    int basic;
};

static ID id_dig;

static int
dig_basic_p(VALUE obj, struct dig_method *cache)
{
    VALUE klass = RBASIC_CLASS(obj);
    if (klass != cache->klass) {
        cache->klass = klass;
        cache->basic = rb_method_basic_definition_p(klass, id_dig);
    }
    return cache->basic;
}

static void
no_dig_method(int found, VALUE data)
{
    if (!found) {
        rb_raise(rb_eTypeError, "%"PRIsVALUE" does not have #dig method", CLASS_OF(data));
    }
}

VALUE
rb_ary_at(VALUE ary, VALUE pos)
{
    return rb_ary_entry(ary, NUM2LONG(pos));
}

VALUE
rb_obj_dig(int argc, VALUE *argv, VALUE obj, VALUE notfound)
{
    struct dig_method hash = {Qnil}, ary = {Qnil};

    for (; argc > 0; ++argv, --argc) {
        if (NIL_P(obj)) return notfound;
        if (!SPECIAL_CONST_P(obj)) {
            switch (BUILTIN_TYPE(obj)) {
                case T_HASH:
                if (dig_basic_p(obj, &hash)) {
                    obj = rb_hash_aref(obj, *argv);
                    continue;
                }
                break;
                case T_ARRAY:
                if (dig_basic_p(obj, &ary)) {
                    obj = rb_ary_at(obj, *argv);
                    continue;
                }
                break;
            }
        }

	int respond = rb_respond_to(obj, id_dig);
        no_dig_method(respond, obj);

        return rb_check_funcall(obj, id_dig, argc, argv);
    }
    return obj;
}

/*
 * call-seq:
 *   hsh.dig(key, ...)                 -> object
 *
 * Extracts the nested value specified by the sequence of <i>idx</i>
 * objects by calling +dig+ at each step, returning +nil+ if any
 * intermediate step is +nil+.
 *
 *   h = { foo: {bar: {baz: 1}}}
 *
 *   h.dig(:foo, :bar, :baz)           #=> 1
 *   h.dig(:foo, :zot, :xyz)           #=> nil
 *
 *   g = { foo: [10, 11, 12] }
 *   g.dig(:foo, 1)                    #=> 11
 */
VALUE
rb_hash_dig(int argc, VALUE *argv, VALUE self)
{
    rb_check_arity(argc, 1, UNLIMITED_ARGUMENTS);
    self = rb_hash_aref(self, *argv);
    if (!--argc) return self;
    ++argv;
    return rb_obj_dig(argc, argv, self, Qnil);
}

/*
 * call-seq:
 *   ary.dig(idx, ...)                 -> object
 *
 * Extracts the nested value specified by the sequence of <i>idx</i>
 * objects by calling +dig+ at each step, returning +nil+ if any
 * intermediate step is +nil+.
 *
 *   a = [[1, [2, 3]]]
 *
 *   a.dig(0, 1, 1)                    #=> 3
 *   a.dig(1, 2, 3)                    #=> nil
 *   a.dig(0, 0, 0)                    #=> TypeError: Fixnum does not have #dig method
 *   [42, {foo: :bar}].dig(1, :foo)    #=> :bar
 */
VALUE
rb_ary_dig(int argc, VALUE *argv, VALUE self)
{
    rb_check_arity(argc, 1, UNLIMITED_ARGUMENTS);
    self = rb_ary_at(self, *argv);
    if (!--argc) return self;
    ++argv;
    return rb_obj_dig(argc, argv, self, Qnil);
}

void
Init_backport_dig(void)
{
#undef rb_intern
#define rb_intern(str) rb_intern_const(str)
    id_dig = rb_intern_const("dig");

    rb_cHash = rb_define_class("Hash", rb_cObject);
    rb_define_method(rb_cHash, "dig", rb_hash_dig, -1);

    rb_cArray  = rb_define_class("Array", rb_cObject);
    rb_define_method(rb_cArray, "dig", rb_ary_dig, -1);
}
