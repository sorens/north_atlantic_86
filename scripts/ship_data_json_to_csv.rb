#!/usr/bin/ruby

require 'csv'
require 'json'

input_path = ARGV[0]
output_path = ARGV[1]

file = File.read input_path
data = JSON.parse(file)

CSV.open(output_path, "w") do |csv|
    csv << ["ID", "NAME", "MAIN_GUN", "AA_GUN", "MISSILE_DEFENSE", "MAX_SPEED", "CARGO_CAPACITY", "DEFENSE_FACTOR", "CLASS_ID", "DESIGNATION", "UNIT_CLASS", "AFFILIATION", "HELICOPTERS", "EW_STRENGTH", "SONAR_STRENGTH", "AIR_RECON", "AIR_EW", "AIR_ASW", "AIR_AWACS", "SSM", "SSM_SALVO", "SSM_MAGAZINE", "ASW", "SAM", "AST"]
    data['ships'].each do |ship|
        id = ship[0]
        name = ship[1]
        main_gun = ship[2]
        aa_gun = ship[3]
        missile_defense = ship[4]
        max_speed = ship[5]
        cargo_capacity = ship[6]
        defense_factor = ship[7]
        designation = ship[8]
        class_id = ship[9]
        unit_class = ship[10]
        affiliation = ship[11]
        csv << [id, name, main_gun, aa_gun, missile_defense, max_speed, cargo_capacity, defense_factor, designation, class_id, unit_class, affiliation]
    end
end