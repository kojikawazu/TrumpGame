#ifndef _MYGAME_ROADERFILE_H
#define _MYGAME_ROADERFILE_H

#ifndef _FSTREAM_
#include <fstream>
#endif

#ifndef _STRING_
#include <string>
#endif

namespace MYGAME
{
	class ResourceRoaderFile
	{
		protected:
			bool isReady;
			std::string resourcePass;
			std::string resourcePass_2;
			std::string resourceKnd;
			std::string extension;
		public:
			ResourceRoaderFile(LPCSTR filepass);
			virtual ~ResourceRoaderFile();

		protected:
			void passload(LPCSTR filepass);
			void checkPass(std::string& str);
			void SettingPass(std::string& pass, int index);
			void loadResourceGraph(std::string& word);
			void loadResource(std::string& word);

	};

	class LoaderFunction
	{
		public:
			bool checkScene(std::ifstream& fs, LPCSTR sceneName);
			bool checkComment_or_finish(std::string& str);
			int isScene( std::string& str , LPCSTR sceneName );
			int isObject( std::string& str , LPCSTR objectName );
	
	};


}

#endif