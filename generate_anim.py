import os
import sys

from optparse import OptionParser
parser = OptionParser()
parser.add_option("-r","--resolution",
	action="store", type="int", nargs=2, dest="resolution")
parser.add_option("-d","--duration",
	action="store", type="int", dest="duration")

(options, args) = parser.parse_args(sys.argv)

print options

#exit()

width = options.resolution[0]
height = options.resolution[1]

cam_rot_angle_y = 0.2
coin_rot_angle = -4
sphere1_step = 0.05

anim_frames = options.duration

mp4_file = "mp4/animation.mp4"

png_file_prefix = "png/image"
png_file_suffix = ".png"

ppm_file_prefix = "ppm/image"
ppm_file_suffix = ".ppm"

sdf_file_prefix = "sdf/frame"
sdf_file_suffix = ".sdf"

sdf_files = []

for frame in range(0, anim_frames):
	sdf = ""

	png_file = png_file_prefix + "{0:03d}".format(frame) + png_file_suffix
	ppm_file = ppm_file_prefix + "{0:03d}".format(frame) + ppm_file_suffix
	sdf_file = sdf_file_prefix + "{0:03d}".format(frame) + sdf_file_suffix

	# materials
	sdf += "define	material mint	1 0 1 0.8 1 1 0.2 1 1 300.0\n"
	sdf += "define	material blue	0.1 0.1 0.1 0.5 0.5 1 0.3 0.3 0.3 700.0\n"
	sdf += "define	material red	0.1 0.1 0.1 1 0.2 0.2 0.5 0.5 0.5 400.0\n"
	sdf += "define	material white	0.9 0.9 0.9 0.9 0.9 0.9 1 1 1 200.0\n"
	sdf += "define	material green  1 0.9 0 0.8 0.8 0 0.8 1 0 900.0\n"
	# geometry
	sdf += "define shape box table -10 0 -10 10 -1 10 white\n"
	sdf += "define shape box box1 0 0 0 1 1 1 mint\n"
	sdf += "define shape box box2 0 0 0 1 1 1 red\n"
	sdf += "define shape sphere sphere1 0 0 0 -2 blue\n"
	sdf += "define shape sphere sphere2 0 0 0 -2.5 green\n"
	# composite
	sdf += "define shape composite root box1 sphere1 box2\n"
	# lights
	sdf += "define light light	5 9 8	1.0 1.0 1.0	0.6 0.6 0.6\n"
	sdf += "define light light2 -20 4 10	1.0 0.7 1.0 0.9 0.3 0.9\n"
	# camera
	sdf += "define camera eye 66.0 0 0 0 0 0 -1 0 1 0\n"
	sdf += "transform eye translate 0 -2 20\n"
	sdf += "transform eye rotate -30 1 0 0\n"

	# transform
	sdf += "transform box1 scale 3 2 3\n"
	sdf += "transform box1 translate -7 0.5 -2\n"
	sdf += "transform box2 rotate 45 1 1 1\n"
	sdf += "transform box2 scale 3 3 3\n"
	sdf += "transform box2 translate 4 3 1\n"
	sdf += "transform sphere1 translate 0 2 "+str(frame * sphere1_step)+"\n"
	sdf += "transform sphere2 scale 0.1 1 0.7\n"
	sdf += "transform sphere2 rotate "+str(frame * coin_rot_angle)+" 0 1 0\n"
	sdf += "transform sphere2 translate -6 2.75 6\n"

	# camera transformation
	sdf += "transform eye rotate " + str(frame * cam_rot_angle_y) + " 0 1 0 \n"
	sdf += "render eye " + ppm_file + " " + str(width) + " " + str(height)

	# write final sdf
	f = open(sdf_file, 'w')
	f.write(sdf)
	f.close()

	# render frame
	print "frame: " + str(frame) + " of "+str(anim_frames)
	os.system("./cmake_out/build/Release/raytracer " + sdf_file + " --no-window")

	os.system("pnmtopng " + ppm_file + " > " + png_file)
	
os.system("ffmpeg -r 24 -i " + png_file_prefix + "%03d" + png_file_suffix + " " + mp4_file)

