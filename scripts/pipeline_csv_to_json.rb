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
nato_pipeline = {}
nato_pipeline_id = []
soviet_pipeline = {}
soviet_pipeline_id = []
nato_ports = {}
soviet_ports = {}
nato_airbases = {}
soviet_airbases = {}
nato_stations_by_id = {}
soviet_stations_by_id = {}
nato_tfs = {}
soviet_tfs = {}

# ID,NAME,CLASS_ID,PIPELINE,SUPPLIES,INFANTRY,TASK FORCE ID,AFFILIATION,X,Y,
# MURMANSK,MURMANSK,96,0,900,400,MURMANSK,SOVIET,0,0,

FIELD_ID                = 0
FIELD_NAME              = 1
FIELD_CLASS_ID          = 2
FIELD_PIPELINE          = 3
FIELD_SUPPLIES          = 4
FIELD_INFANTRY          = 5
FIELD_TASK_FORCE_ID     = 6
FIELD_AFFILIATION       = 7
FIELD_X                 = 8
FIELD_Y                 = 9
FIELD_MISSION           = 10

# CLASS_ID =>
# PORT: 
#   SOVIET: 96 (MURMANSK, RIGA)
#   NATO: 98 (AMERICA)
# AIRBASE: 
#   SOVIET: 95 (HAMBURG, BERGE, FAROES, ICELAND)
#   NATO: 97 (SCAPA FLOW, FAROES, ICELAND)

# station: MURMANSK => 40, 9
# station: ICELAND => 13, 15
# station: FAROES => 21, 19
# station: BERGEN => 29, 20
# station: RIGA => 40, 22
# station: SCAPA FLOW => 24, 23
# station: HAMBURG => 31, 29
# station: AMERICA => 1, 34

CSV.foreach(input_path, {headers: true}) do |row|
    if row.size == 11
        id = row[FIELD_ID]
        name = row[FIELD_NAME]
        class_id = row[FIELD_CLASS_ID]              # treat as a string ID, even if its a number
        arrival_time = row[FIELD_PIPELINE].to_i
        supplies = row[FIELD_SUPPLIES].to_i
        infantry = row[FIELD_INFANTRY].to_i
        task_force_id = row[FIELD_TASK_FORCE_ID]    # treat as a string ID, even if its a number
        affiliation = row[FIELD_AFFILIATION]
        x = row[FIELD_X].to_i
        y = row[FIELD_Y].to_i
        mission = field_or_empty(row[FIELD_MISSION])

        obj = []
        obj << name
        obj << id
        obj << class_id
        obj << arrival_time
        obj << supplies
        obj << infantry
        obj << task_force_id
        obj << affiliation
        obj << x
        obj << y
        obj << mission

        if (id == "MURMANSK" || id == "RIGA")
            # MURMANSK OR RIGA
            soviet_ports[id] = obj
            # store the pipeline as the task_force_id as a string
            soviet_stations_by_id[id] = name
            soviet_pipeline[soviet_stations_by_id[task_force_id]] = []
            soviet_pipeline_id << task_force_id
        elsif (id == "AMERICA")
            # AMERICA
            nato_ports[id] = obj
            # store the pipeline as the task_force_id as a string
            nato_stations_by_id[id] = name
            nato_pipeline[nato_stations_by_id[task_force_id]] = []
            nato_pipeline_id << task_force_id
        elsif (class_id == "95" && affiliation == "SOVIET")
            soviet_airbases[id] = obj
            soviet_stations_by_id[id] = name
        elsif (class_id == "97" && affiliation == "NATO")
            nato_airbases[id] = obj
            nato_stations_by_id[id] = name
        else
            # check task_force_id, if it matches a port, that ship is in that port
            if (affiliation == "SOVIET")
                if (soviet_pipeline_id.include?(task_force_id))
                    # a ship in port
                    soviet_pipeline[soviet_stations_by_id[task_force_id]] << obj
                else
                    # ship in a task force
                    if (!soviet_tfs.key?(task_force_id))
                        map = {}
                        map["mission"] = obj[10]
                        map["x"] = obj[8]
                        map["y"] = obj[9]
                        map["units"] = []
                        soviet_tfs[task_force_id] = map
                    end
                    soviet_tfs[task_force_id]["units"] << obj
                end
            elsif (affiliation == "NATO")
                if (nato_pipeline_id.include?(task_force_id))
                    # a ship in port
                    nato_pipeline[nato_stations_by_id[task_force_id]] << obj
                else
                    # ship in a task force
                    if (!nato_tfs.key?(task_force_id))
                        map = {}
                        map["mission"] = obj[10]
                        map["x"] = obj[8]
                        map["y"] = obj[9]
                        map["units"] = []
                        nato_tfs[task_force_id] = map
                    end
                    nato_tfs[task_force_id]["units"] << obj
                end
            end
        end
    end
end

data["scenario"] = {}
data["scenario"]["nato_pipeline"] = nato_pipeline
data["scenario"]["soviet_pipeline"] = soviet_pipeline
data["scenario"]["nato_ports"] = nato_ports
data["scenario"]["soviet_ports"] = soviet_ports
data["scenario"]["nato_airbases"] = nato_airbases
data["scenario"]["soviet_airbases"] = soviet_airbases
data["scenario"]["nato_tfs"] = nato_tfs
data["scenario"]["soviet_tfs"] = soviet_tfs

File.open(output_path, "w") do |file|
    file.write(JSON.pretty_generate(data))
end