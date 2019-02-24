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
naval_stations = []

# NAME,TYPE,AFFILIATION,MAIN_GUNS,LIGHT_GUNS,MISSILE_DEFENSE,
# CARGO_CAPACITY,DEFENSE_FACTOR,SSM,SSM_SALVO_RATE,
# SSM_MAGAZINE_CAPACITY,ASW,SAM,AST,HELICOPTERS,EW_STRENGTH,
# SONAR_STRENGTH

FIELD_NAME              = 0
FIELD_TYPE              = 1
FIELD_AFFILIATION       = 2
FIELD_MAIN_GUN          = 3
FIELD_AA_GUN            = 4
FIELD_MD                = 5
FIELD_CC                = 6
FIELD_DF                = 7
FIELD_SSM               = 8
FIELD_SSM_SALVO         = 9
FIELD_SSM_MAGAZINE      = 10
FIELD_ASW               = 11
FIELD_SAM               = 12
FIELD_AST               = 13
FIELD_HELICOPTERS       = 14
FIELD_EW_STRENGTH       = 15
FIELD_SONAR_STRENGTH    = 16

CSV.foreach(input_path, {headers: true}) do |row|
    if row.size == 17
        naval_station = []
        naval_station << row[FIELD_NAME]
        naval_station << row[FIELD_TYPE]
        naval_station << row[FIELD_AFFILIATION]
        naval_station << row[FIELD_MAIN_GUN].to_i
        naval_station << row[FIELD_AA_GUN].to_i
        naval_station << row[FIELD_MD].to_i
        naval_station << row[FIELD_CC].to_i
        naval_station << row[FIELD_DF].to_i
        naval_station << field_or_empty(row[FIELD_SSM])
        naval_station << row[FIELD_SSM_SALVO].to_i
        naval_station << row[FIELD_SSM_MAGAZINE].to_i
        naval_station << field_or_empty(row[FIELD_ASW])
        naval_station << field_or_empty(row[FIELD_SAM])
        naval_station << field_or_empty(row[FIELD_AST])
        naval_station << row[FIELD_HELICOPTERS].to_i
        naval_station << row[FIELD_EW_STRENGTH].to_i
        naval_station << row[FIELD_SONAR_STRENGTH].to_i
        naval_stations << naval_station
    end
end

data["naval_stations"] = naval_stations

File.open(output_path, "w") do |file|
    file.write(JSON.pretty_generate(data))
end