#ifndef CTM_MATERIAL_H
#define CTM_MATERIAL_H

namespace ctm
{

//////
//Material
class Material
{
public:
	//Use
		virtual void Use() = 0;
		virtual void Cleanup() = 0;
};
//////

}

#endif