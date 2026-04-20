set terminal png size 800,600
set output "grafica.png"

set title "Insertion Sort vs Merge Sort"
set xlabel "n"
set ylabel "Tiempo (microsegundos)"
set grid
set key top left

plot "resultados.dat" using 1:2 with lines lw 2 title "Insertion", \
     "resultados.dat" using 1:3 with lines lw 2 title "Merge"
