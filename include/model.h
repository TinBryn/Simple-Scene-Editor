//
// Created by kieran on 23/05/19.
//

#ifndef CITS3003_MODEL_H
#define CITS3003_MODEL_H

struct Model
{
    unsigned int vao;
};

Model createModel(unsigned int program);

void resetModel(Model model, unsigned int program);

#endif //CITS3003_MODEL_H
