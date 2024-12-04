import gpxpy
import gpxpy.gpx
import matplotlib.pyplot as plt

# Parsing an existing file:
# -------------------------

gpx_file = open('data/2023-05-11_15-11-56_gpx測試.gpx', 'r')

gpx = gpxpy.parse(gpx_file)

for track in gpx.tracks:
    for segment in track.segments:
        x = [point.longitude for point in segment.points]
        y = [point.latitude for point in segment.points]
        plt.plot(x, y)
        for point in segment.points:
            print(f'Point at ({point.latitude},{point.longitude}) -> {point.elevation}')

ax = plt.gca()
ax.set_aspect('equal', adjustable='datalim')
ax.ticklabel_format(useOffset=False)
plt.savefig('output/gpx.png')

for waypoint in gpx.waypoints:
    print(f'waypoint {waypoint.name} -> ({waypoint.latitude},{waypoint.longitude})')

for route in gpx.routes:
    print('Route:')
    for point in route.points:
        print(f'Point at ({point.latitude},{point.longitude}) -> {point.elevtion}')