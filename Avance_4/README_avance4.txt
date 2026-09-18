ya en este avance resuelvo los problemas posteriores a una eliminación de ficha, es decir: gravedad, relleno y cascadas

aplicarGravedad() hace que las fichas caigan cuando tienen debajo una ficha vacia

rellenarVacios() busca esas posiciones vacías y las reemplaza por nuevas fichas aleatorias entre 0 y 5, o sea A-F (posterior a la gravedad)

resolverCascadas() coordina todo el proceso, es decir, primero elimina combinaciones, luego aplica gravedad, rellena los vacíos y vuelve a buscar combinaciones. Repite hasta que ya no haya mas 
