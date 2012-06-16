#!/usr/bin/env ruby
fin = File.new(ARGV[0],"w")
fout = File.new(ARGV[1],"w")
NUMLEN = 10000
WORDCOUNT = 50000
WORDLEN = 100

words = Array.new(WORDCOUNT)
words.each_index{|i| words[i]=Array.new(WORDLEN-i.to_s.length){0}.to_s + i.to_s}
fout<<NUMLEN/WORDLEN<<"\n"
for i in 1..NUMLEN/WORDLEN do
	ind = rand(WORDCOUNT);
	fout<<words[ind]<<(i == NUMLEN/WORDLEN ? "" : " ")	
	fin<<words[ind]
end

fin<<"\n"<<WORDCOUNT<<"\n"
words.each{|i| fin<<i<<"\n"}

fin.close
fout.close
