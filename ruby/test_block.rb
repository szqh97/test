puts "You gave #{ARGV.size} argument"
p ARGV
def call_block
    puts "Start of call_block"
    yield
    yield
    puts "end of call_block"
end

call_block {puts "In the block"}
