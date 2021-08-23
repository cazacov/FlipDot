#include "BaseAnimation.h"

BaseAnimation::~BaseAnimation() {}

void BaseAnimation::begin(Display &display...) {isActive = true;}
void BaseAnimation::end(Display &display) {isActive = false;}
void BaseAnimation::nextStep(Display &display) {}