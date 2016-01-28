describe Hash do
  describe '#dig' do
    specify { expect({foo: {bar: {baz: 1}}}.dig(:foo, :bar, :baz)).to eq 1 }
    specify { expect({foo: {bar: {baz: 1}}}.dig(:foo, :bar, :xyz)).to eq nil }
    specify { expect({foo: [10, 11, 12]}.dig(:foo, 1)).to eq 11 }
    specify { expect({}.dig(nil)).to be_nil }
  end
end

describe Array do
  describe '#dig' do
    specify { expect([[1, [2, 3]]].dig(0, 1, 1)).to eq 3 }
    specify { expect([[1, [2, 3]]].dig(1, 2, 3)).to eq nil }
    specify { expect { [[1, [2, 3]]].dig(0, 0, 0) }.to raise_error(TypeError, 'Fixnum does not have #dig method') }
  end
end

describe OpenStruct do
  let(:address) { OpenStruct.new('city' => "Anytown NC", 'zip' => 12345) }
  let(:person)  { OpenStruct.new('name' => 'John Smith', 'address' => address) }

  specify { expect(person.dig(:address, 'zip')).to eq 12345 }
  specify { expect(person.dig(:business_address, 'zip')).to be_nil }
end
