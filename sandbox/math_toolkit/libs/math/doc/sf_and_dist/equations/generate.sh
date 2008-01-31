#
# Generates SVG and PNG files from the MML masters.
#
# Paths to tools come first, change these to match your system:
#
math2svg='C:\download\open\SVGMath-0.3.1\math2svg.py'
python=/cygdrive/c/Python25/python.exe
inkscape=/cygdrive/c/progra~1/Inkscape/inkscape
# Image DPI:
dpi=120

for mmlfile in $*; do
	svgfile=$(basename $mmlfile .mml).svg
	pngfile=$(basename $svgfile .svg).png
	tempfile=temp.mml
	# strip html wrappers put in by MathCast:
	cat $svgfile | tr -d "\r\n" | sed -e 's/.*\(<math[^>]*>.*<\/math>\).*/\1/' > $tempfile
	
	echo Generating $svgfile
	$python $math2svg $tempfile > $svgfile
	echo Generating $pngfile
	$inkscape -d $dpi -e $(cygpath -a -w $pngfile) $(cygpath -a -w $svgfile)
	rm $tempfile
done


