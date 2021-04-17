#ifndef _PROJECTX_TESTSHADER_H
#define _PROJECTX_TESTSHADER_H

#ifndef _MYGAME_SHENE_H
#include <SceneMethod.h>
#endif

namespace NanairoProject
{
	class TestShader : public MYGAME::Scene
	{
	protected:
		void Draw3D(){}
		void Draw2D(){}
		
	public:
		TestShader();
		~TestShader(){}

		void Init();
		void Recircle(){}
		void Step(){}
		void Draw();
		void Atack(){}
		void Dispose();
		void Del(){}
	};
}

#endif