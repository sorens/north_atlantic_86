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
aircrafts = []

# ORDER,NAME,TYPE,AFFILIATION,RANGE,AVERAGE_DAMAGE,
# ACCURACY_RATING,SURFACE_SKIMMING,SAM_SALVO_RATE

FIELD_NAME                  = 0
FIELD_DESIGNATION           = 1
FIELD_RANGE                 = 2
FIELD_WEAPON_SYSTEM         = 3
FIELD_CARRIER_AIRCRAFT      = 4
FIELD_AFFILIATION           = 5
FIELD_ECM_RATING            = 6
FIELD_DOGFIGHT_RATING       = 7
FIELD_BOMBER_ACCURACY       = 8
FIELD_RADAR_CAPABILITY      = 9
FIELD_LRCAP_MISSILE_EW_AVG  = 10
FIELD_LRCAP_MISSILE_EW_MAX  = 11
FIELD_LRCAP_MISSILE_AVG     = 12
FIELD_LRCAP_MISSILE_MAX     = 13
FIELD_LRCAP_DOGFIGHT_EW_AVG = 14
FIELD_LRCAP_DOGFIGHT_EW_MAX = 15
FIELD_LRCAP_DOGFIGHT_AVG    = 16
FIELD_LRCAP_DOGFIGHT_MAX    = 17
FIELD_CAP_MISSILE_EW_AVG    = 18
FIELD_CAP_MISSILE_EW_MAX    = 19
FIELD_CAP_MISSILE_AVG       = 20
FIELD_CAP_MISSILE_MAX       = 21
FIELD_CAP_DOGFIGHT_EW_AVG   = 22
FIELD_CAP_DOGFIGHT_EW_MAX   = 23
FIELD_CAP_DOGFIGHT_AVG      = 24
FIELD_CAP_DOGFIGHT_MAX      = 25

CSV.foreach(input_path, {headers: true}) do |row|
    if row.size == 26
        aircraft = []
        aircraft << row[FIELD_NAME]
        aircraft << row[FIELD_DESIGNATION]
        aircraft << row[FIELD_RANGE].to_i
        aircraft << field_or_empty(row[FIELD_WEAPON_SYSTEM])
        aircraft << true if (row[FIELD_CARRIER_AIRCRAFT] == "TRUE")
        aircraft << false if (row[FIELD_CARRIER_AIRCRAFT] == "FALSE")
        aircraft << row[FIELD_AFFILIATION]
        aircraft << row[FIELD_ECM_RATING].to_i
        aircraft << row[FIELD_DOGFIGHT_RATING].to_i
        aircraft << row[FIELD_BOMBER_ACCURACY].to_i
        aircraft << row[FIELD_RADAR_CAPABILITY].to_i

        aircraft << row[FIELD_LRCAP_MISSILE_EW_AVG].to_i
        aircraft << row[FIELD_LRCAP_MISSILE_EW_MAX].to_i
        aircraft << row[FIELD_LRCAP_MISSILE_AVG].to_i
        aircraft << row[FIELD_LRCAP_MISSILE_MAX].to_i
        aircraft << row[FIELD_LRCAP_DOGFIGHT_EW_AVG].to_i
        aircraft << row[FIELD_LRCAP_DOGFIGHT_EW_MAX].to_i
        aircraft << row[FIELD_LRCAP_DOGFIGHT_AVG].to_i
        aircraft << row[FIELD_LRCAP_DOGFIGHT_MAX].to_i
        aircraft << row[FIELD_CAP_MISSILE_EW_AVG].to_i
        aircraft << row[FIELD_CAP_MISSILE_EW_MAX].to_i
        aircraft << row[FIELD_CAP_MISSILE_AVG].to_i
        aircraft << row[FIELD_CAP_MISSILE_MAX].to_i
        aircraft << row[FIELD_CAP_DOGFIGHT_EW_AVG].to_i
        aircraft << row[FIELD_CAP_DOGFIGHT_EW_MAX].to_i
        aircraft << row[FIELD_CAP_DOGFIGHT_AVG].to_i
        aircraft << row[FIELD_CAP_DOGFIGHT_MAX].to_i
        aircrafts << aircraft
    end
end

data["aircrafts"] = aircrafts

File.open(output_path, "w") do |file|
    file.write(JSON.pretty_generate(data))
end