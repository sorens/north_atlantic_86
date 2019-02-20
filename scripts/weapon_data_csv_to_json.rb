#!/usr/bin/ruby

require 'csv'
require 'json'

def field_or_empty(field)
    return field if !field.nil? && !field.empty?
    return ""
end

input_path = ARGV[0]
output_path = ARGV[1]

data = {}
weapons = []

# ORDER,NAME,TYPE,AFFILIATION,RANGE,AVERAGE_DAMAGE,
# ACCURACY_RATING,SURFACE_SKIMMING,SAM_SALVO_RATE

FIELD_ORDER             = 0
FIELD_NAME              = 1
FIELD_TYPE              = 2
FIELD_AFFILIATION       = 3
FIELD_RANGE             = 4
FIELD_AVERAGE_DAMAGE    = 5
FIELD_ACCURACY_RATING   = 6
FIELD_SURFACE_SKIMMING  = 7
FIELD_SAM_SALVO_RATE    = 8

CSV.foreach(input_path, {headers: true}) do |row|
    if row.size == 9
        weapon = []
        weapon << row[FIELD_NAME]
        weapon << row[FIELD_TYPE]
        weapon << row[FIELD_AFFILIATION]
        weapon << row[FIELD_RANGE].to_i
        weapon << row[FIELD_AVERAGE_DAMAGE].to_i
        weapon << row[FIELD_ACCURACY_RATING].to_i
        weapon << true if (row[FIELD_SURFACE_SKIMMING] == "TRUE")
        weapon << false if (row[FIELD_SURFACE_SKIMMING] == "FALSE")
        weapon << row[FIELD_SAM_SALVO_RATE].to_i
        weapons << weapon
    end
end

data["weapons"] = weapons

File.open(output_path, "w") do |file|
    file.write(JSON.pretty_generate(data))
end