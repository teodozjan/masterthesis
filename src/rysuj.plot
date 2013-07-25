set locale 'pl_PL.UTF-8'
set decimal ','
set decimalsign ','
set terminal png
set autoscale

#xyCallInt.xy
#xyCallLen.xy
#xyQueLen-f.xy
#xyQueLen.xy
#xyQueTime.xy
#xySrvUsage-f.xy
#xySrvUsage.xy`



mu=25; n=47; p=0.56
set samples n+1;
i(x)=int(x+.1)
pd(x)=mu**x*exp(-mu)/i(x)!
bd(x)=n!/(i(x)!*(n-i(x))!)*p**x*(1-p)**(n-x)
set output "xyCallInt.png"
plot "xyCallInt.xy" with points title "Pomiar ",\
     pd(x) with lines title "rozklad poissona"
     #bd(x) with lines 
     


set output "xyCallLen.png"
plot "xyCallLen.xy" using 1:2 title 'Dlugosc polaczenia' with linespoints

#set output "xyCallPerMin.png"
#plot "xyCallPerMin.xy" title 'Połaczeń na minutę'

set output "xySrvFlow.png"
plot "xySrvFlow.xy"


set output "xySrvUsage-f.png"
#set nologscale y
plot "xySrvUsage-f.xy" title "Ilosc zajetych serwerow w funkcji czasu" 

set output "xyQueTime.png"
plot "xyQueTime.xy"


set output "xySrvUsage.png"
#set logscale y 10
plot "xySrvUsage.xy" with linespoints title "Prawdopodobienstwo ze bedzie zajeta okreslona ilosc serwerow"
