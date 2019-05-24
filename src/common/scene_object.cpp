//
// Created by kieran on 24/05/19.
//

#include <scene_object.h>

SceneObject::SceneObject(int model, int texture)
        : location{}, scale{1}, angles{}, diffuse{}, specular{}, ambient{}, shine{}, color{},
          brightness{}, modelId{model}, textureId{texture}, texScale{}
{

}