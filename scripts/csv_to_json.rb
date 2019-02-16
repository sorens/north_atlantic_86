#!/usr/bin/ruby

require 'csv'
require 'json'

require 'csv'
require 'json'

input_path = ARGV[0]
output_path = ARGV[1]

ships = {}

CSV.foreach(input_path, {headers: true}) do |row|
    if row.size == 29
    end
end