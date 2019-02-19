#!/usr/bin/ruby

require 'csv'
require 'json'

require 'csv'
require 'json'

def field_or_empty(field)
    return field if !field.nil? && !field.empty?
    return ""
end

input_path = ARGV[0]
output_path = ARGV[1]

data = {}
ships = []

# ORDER,ID,NAME,MAIN_GUN,AA_GUN,MISSILE_DEFENSE,MAX_SPEED,
# CARGO_CAPACITY,DEFENSE_FACTOR,CLASS_ID,DESIGNATION,UNIT_CLASS,
# AFFILIATION,HELICOPTERS,EW_STRENGTH,SONAR_STRENGTH,AIR_RECON,
# AIR_EW,AIR_ASW,AIR_AWACS,SSM,SSM_SALVO,SSM_MAGAZINE,ASW,SAM,AST,
# PRIMARY_ROLE,SECONDARY_ROLE,TERTIARY_ROLE
# 1,CVN-68,Nimitz,0,0,75,30,72,97,1,CVN,Nimitz,NATO,6,6,0,4,4,10,4,,,,,,,ATTACK,,

FIELD_ID                = 1
FIELD_NAME              = 2
FIELD_MAIN_GUN          = 3
FIELD_AA_GUN            = 4
FIELD_MD                = 5
FIELD_MS                = 6
FIELD_CC                = 7
FIELD_DF                = 8
FIELD_CLASS_ID          = 9
FIELD_DESIGNATION       = 10
FIELD_UNIT_CLASS        = 11
FIELD_AFFILIATION       = 12
FIELD_HELICOPTERS       = 13
FIELD_EW_STRENGTH       = 14
FIELD_SONAR_STRENGTH    = 15
FIELD_AIR_RECON         = 16
FIELD_AIR_EW            = 17
FIELD_AIR_ASW           = 18
FIELD_AIR_AWACS         = 19
FIELD_SSM               = 20
FIELD_SSM_SALVO         = 21
FIELD_SSM_MAGAZINE      = 22
FIELD_ASW               = 23
FIELD_SAM               = 24
FIELD_AST               = 25
FIELD_PRIMARY_ROLE      = 26
FIELD_SECONDARY_ROLE    = 27
FIELD_TERTIARY_ROLE     = 28

CSV.foreach(input_path, {headers: true}) do |row|
    if row.size == 29
        ship = []
        ship << row[FIELD_ID]
        ship << row[FIELD_NAME]
        ship << row[FIELD_MAIN_GUN].to_i
        ship << row[FIELD_AA_GUN].to_i
        ship << row[FIELD_MD].to_i
        ship << row[FIELD_MS].to_i
        ship << row[FIELD_CC].to_i
        ship << row[FIELD_DF].to_i
        ship << row[FIELD_CLASS_ID].to_i
        ship << row[FIELD_DESIGNATION]
        ship << row[FIELD_AFFILIATION]
        ship << row[FIELD_HELICOPTERS].to_i
        ship << row[FIELD_EW_STRENGTH].to_i
        ship << row[FIELD_SONAR_STRENGTH].to_i
        ship << row[FIELD_AIR_RECON].to_i
        ship << row[FIELD_AIR_EW].to_i
        ship << row[FIELD_AIR_ASW].to_i
        ship << row[FIELD_AIR_AWACS].to_i
        ship << field_or_empty(row[FIELD_SSM])
        ship << row[FIELD_SSM_SALVO].to_i
        ship << row[FIELD_SSM_MAGAZINE].to_i
        ship << field_or_empty(row[FIELD_ASW])
        ship << field_or_empty(row[FIELD_SAM])
        ship << field_or_empty(row[FIELD_AST])
        ship << field_or_empty(row[FIELD_PRIMARY_ROLE])
        ship << field_or_empty(row[FIELD_SECONDARY_ROLE])
        ship << field_or_empty(row[FIELD_TERTIARY_ROLE])
        ships << ship
    end
end

data["ships"] = ships

File.open(output_path, "w") do |file|
    file.write(JSON.pretty_generate(data))
end