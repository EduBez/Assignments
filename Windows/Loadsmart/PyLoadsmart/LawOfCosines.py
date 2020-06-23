import math
from collections import namedtuple

# Named tuple
LatLng = namedtuple('LatLng', 'lat, lng')


def Distance(orig, dest):
    """ Support function to calculate the 'Distance' between Latitude & Longitude points

    This algorithm is described in the article;
    "Calculate distance, bearing and more between Latitude/Longitude points"
    https://www.movable-type.co.uk/scripts/latlong.html """

    result = math.acos(math.cos(math.radians(90 - orig.lat)) * math.cos(math.radians(90 - dest.lat)) +
                       math.sin(math.radians(90 - orig.lat)) * math.sin(math.radians(90 - dest.lat)) *
                       math.cos(math.radians(orig.lng - dest.lng))) * 6371
    return result
