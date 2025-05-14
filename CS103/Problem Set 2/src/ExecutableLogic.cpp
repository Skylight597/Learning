#include "ExecutableLogic.h"
#include <stdexcept>

/* ∃x. Cat(x) */
bool isFormulaTrueFor_partI(std::set<Entity> world) {
    /* TODO: Delete this line and the next two lines, then implement this function. */
    (void) world;
    throw std::runtime_error("Not implemented.");
}

/* ∀x. Robot(x) */
bool isFormulaTrueFor_partII(std::set<Entity> world) {
    /* TODO: Delete this line and the next two lines, then implement this function. */
    (void) world;
    throw std::runtime_error("Not implemented.");
}

/* ∃x. (Person(x) ∧ Loves(x, x)) */
bool isFormulaTrueFor_partIII(std::set<Entity> world) {
    /* TODO: Delete this line and the next two lines, then implement this function. */
    (void) world;
    throw std::runtime_error("Not implemented.");
}

/* ∀x. (Cat(x) → Loves(x, x)) */
bool isFormulaTrueFor_partIV(std::set<Entity> world) {
    /* TODO: Delete this line and the next two lines, then implement this function. */
    (void) world;
    throw std::runtime_error("Not implemented.");
}

/*
 * ∀x. (Cat(x) →
 *   ∃y. (Person(y) ∧ ¬Loves(x, y))
 * )
 */
bool isFormulaTrueFor_partV(std::set<Entity> world) {
    /* TODO: Delete this line and the next two lines, then implement this function. */
    (void) world;
    throw std::runtime_error("Not implemented.");
}

/*
 * ∃x. (Robot(x) ↔
 *   ∀y. Loves(x, y)
 * )
 */
bool isFormulaTrueFor_partVI(std::set<Entity> world) {
    /* TODO: Delete this line and the next two lines, then implement this function. */
    (void) world;
    throw std::runtime_error("Not implemented.");
}
