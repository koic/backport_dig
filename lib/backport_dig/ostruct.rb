require 'ostruct'

class OpenStruct
  #
  # Retrieves the value object corresponding to the each +name+
  # objects repeatedly.
  #
  #   address = OpenStruct.new('city' => "Anytown NC", 'zip' => 12345)
  #   person = OpenStruct.new('name' => 'John Smith', 'address' => address)
  #   person.dig(:address, 'zip') # => 12345
  #   person.dig(:business_address, 'zip') # => nil
  #
  def dig(name, *names)
    begin
      name = name.to_sym
    rescue NoMethodError
      return
    end
    @table.dig(name, *names)
  end
end
