#include "scattersearch.hpp"

// Generar Soluciones:
//  Aplica un método de generación con diversidad del conjunto
//  de soluciones en "P" de tamaño «popsize».
void solutions_generation()
{
}

// Mejorar Soluciones:
//  Aplica un método de búsqueda local para mejorar las
//  soluciones generadas en el paso previo.
void solutions_improvment()
{
}

// Construir el conjunto de referencia RefSet:
//  Elegir las mejores «b» soluciones para construir el conjunto RefSet.
//  El conjunto RefSet es un conjunto de «b» soluciones que se usarán para
//  generar nuevas soluciones al combinarlas por algún método.
void refset_build()
{
}

// Inicializar:
//  Identificar la mejor solución en RefSet como la mejor actual.
void initialize()
{
}

// Combinar Soluciones:
//  Generar intentos de soluciones usando todos los pares de soluciones de RefSet,
//  tal que al menos una solucion de cada una sea nueva.
void solutions_combination()
{
}

// Modificar el conjunto de referencia
//  Elegir las mejores «b» soluciones de la unión entre RefSet con el conjunto
//  «b(b-1)/2» de soluciones generadas en el paso anterior.
void refset_modification()
{
}

// Modificar el mejor:
//  Identificar la mejor solución de RefSet
void best_modification()
{
}

// Reconstruir RefSet:
//  Eliminar las «b/2» soluciones en RefSet.
//  Generar «popsize» soluciones mejoradas aplicando "solutions_generation" y
//  "solutions_improvment".
//  Elegir «b/2» soluciones "diversas" y agregarlas a RefSet.
void refset_rebuild()
{
}
