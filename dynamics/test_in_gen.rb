#!/usr/bin/env ruby

def min (x,y)
	return x < y ? x : y
end

MAX_NUMBER_LENGTH = 20
MAX_WORD_COUNT = 1000
MAX_WORD_LENGTH = 100
ARGV.each do |a|
	fout = File.new(a,"w")
	numlen = rand(MAX_NUMBER_LENGTH)
	for i in 1..numlen do
		fout<<rand(10)
	end
	wordCount = rand(MAX_WORD_COUNT)
	fout<<"\n"<<wordCount<<"\n"
	for i in 1..wordCount+1 do
		thisWrdLen  = rand(min(numlen,MAX_WORD_LENGTH))
		for j in 1..thisWrdLen do
			fout<<rand(10)
		end
		fout<<"\n"
	end
end


