import operator

from collections import defaultdict
from LawOfCosines import Distance
from LawOfCosines import LatLng


def GenKey(product, state, city):
    """ Generate a unique key """ 
    return product + ': ' + state + '-' + city


def CreateAssociation(cargos, trucks):
    """ Build the collection containing the 'Cargos-Trucks' association """ 

    # Collection to hold 'Cargo-Truck' associations
    result = defaultdict(list)

    # Iterate over every cargo to be delivered
    # Complexity: O(N)
    for c in cargos:
        # A unique key must be created to avoid conflict
        # between products with the same name
        key = GenKey(c[0], c[2], c[1]) # [0] product, [2] origin_state, [1] origin_city

        orig = LatLng(c[3], c[4]) # lat, lng
        dest = LatLng(c[7], c[8]) # lat, lng

        # Save the distance the cargo has to move to arrive at its destination
        cargo_dist = Distance(orig, dest)

        # Iterate over every truck available
        # Complexity: O(N)
        for t in trucks:
            # Save the distance the truck has to move to arrive at the cargo location
            truck_dist = Distance(LatLng(t[3], t[4]), orig)

            # Cargo distance to its destination must be added
            # to the distance the truck has to travel
            truck_dist += cargo_dist

            # Add the 'Cargo-Truck' association to the collection
            value = (t[0], truck_dist)
            result[key].append(value)
   
    return result


def ShortestDistance(mmp, product, truck):
    """ Find the shortest distance for a cargo delivery """

    # Collection to hold trucks and distances
    distances = defaultdict(list)

    # Filter the 'Cargo-Truck' collection for the desired product
    filtered = {key: value for key, value in mmp.items() if key == product}

    for item in filtered.items():
        # Unpack first tuple
        key, trucks_distances = item
        for val in trucks_distances:
            # Unpack second tuple
            truck_name, distance = val
            # A truck can't be used for more than one delivery
            if truck_name == truck:
                continue
            # Save truck and distance
            distances[truck_name] = distance

    # Compute the shortest distance
    result = min(distances.items(), key=operator.itemgetter(1))
    return result


def OptimalMapping(cargos, mmp):
    """ Discover and store the optimal truck for each possible cargo delivery """

    result = defaultdict(list)

    # Iterate over every cargo to be delivered
    # Complexity: O(N)
    for c in cargos:
        # Compose the unique key
        key = GenKey(c[0], c[2], c[1]) # [0] product, [2] origin_state, [1] origin_city

        # Find the shortest distance for this cargo delivery
        cargo_truck = ShortestDistance(mmp, key, "")
        # Save the truck. Each truck can only carry up to one cargo
        truck = cargo_truck[0]

        # Verify if the truck is already associated with the cargo
        # Complexity: O(N)
        found = False
        for item in result.items():
            # Unpack first tuple
            name, val = item
            # Unpack second tuple
            truck_name, distance = val

            if truck == truck_name:
                found = True
                break

        if not found:
            # Store result
            result[key] = cargo_truck
        else:
            # Search for a different truck that has the SECOND BEST shortest distance
            cargo_truck = ShortestDistance(mmp, key, truck)
            # Store result
            result[key] = cargo_truck

    return result
