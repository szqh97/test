class BookInStock
    attr_reader :isbn
    attr_accessor :price
    def initialize(isbn, price)
        @isbn = isbn
        @price = Float(price)
    end
    def to_s
        "ISBS: #{@isbn}, Price: #{@price}"
    end

    def price
        @price
    end
    def price=(newprice)
        @price = newprice
    end

    def isbn
        @isbn
    end
end

b = BookInStock.new("isbn3", 33)

b.price = b.price * 0.57
puts b

puts "ISBN: #{b.isbn}"
puts "Price : #{b.price}"
