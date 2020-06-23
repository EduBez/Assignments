import csv


def ParseFile(file_name, iid):
    """ Function to parse 'csv' data file contents """
    
    # Open file
    file = open(file_name, newline='')

    # Retrieve a file reader iterator
    lines = csv.reader(file)
    # Assume first line has columns names and skip it
    next(lines)

    # Store parsed file content    
    result = list()

    if iid == 'Cargo':
        # Read 'Cargo' data
        for row in lines:
            product      = row[0]
            origin_city  = row[1]
            origin_state = row[2]
            origin_lat   = float(row[3])
            origin_lng   = float(row[4])
            dest_city    = row[5]
            dest_state   = row[6]
            dest_lat     = float(row[7])
            dest_lng     = float(row[8])
        
            result.append([product,
                           origin_city,
                           origin_state,
                           origin_lat,
                           origin_lng,
                           dest_city,
                           dest_state,
                           dest_lat,
                           dest_lng])
    elif iid == 'Trucks':
        # Read 'Trucks' data
        for row in lines:
            truck = row[0]
            city  = row[1]
            state = row[2]
            lat   = float(row[3])
            lng   = float(row[4])
        
            result.append([truck, city, state, lat, lng])

    return result
