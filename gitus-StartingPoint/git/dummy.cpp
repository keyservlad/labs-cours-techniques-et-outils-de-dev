#include "dummy.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/uuid/detail/sha1.hpp>



// utilis�e pour les tests -- � �liminer �ventuellement
int GetAnswerToLifeUniverseAndEverything() 
{
	return 42;
}

// cette fonction est d�di�e � �tre �limin�e -- seulement de test
void TestDeTrucs() throw(boost::filesystem::filesystem_error) // le throw ici est "deprecated". Il est juste conserver � titre de documentation -- vous n'avez pas besoin de le mettre dans votre code
{
	/*
		Le but de la fonction est de pr�senter les techniques utiles pour la
		r�alisation du travail
		Ceci inclus:
				l'utilisation de boost::filesystem
				la g�n�ration de sha1
				l'utilisation de zlib (de boost)

		Il manque beaucoup de trucs ici comme, par exemple, la gestion des erreurs
		Ce n'est pas le but de ce fichier de faire ce genre de d�tail
	*/

	using boost::uuids::detail::sha1;
	using std::ifstream;
	using std::string;

    // auto...auto everywhere
    // just to not bothered about the type and let the compiler figure that out...i'm lazy
	const auto filePath = "truc.txt";

	// lecture du fichier
	ifstream file(filePath);	// pas besoin de gerer l'acces
								// mais il faut s'assurer que le fichier existe

    // lecture automatique du contenu et insertion dans une string
	string content{	std::istreambuf_iterator<char>(file),
					std::istreambuf_iterator<char>() };
    // the file does not exists, so there is nothing to read -- it was made here for demo purposes


	//---------------------------------------------
	// le sha
	// https://pragmaticjoe.blogspot.com/2015/02/how-to-generate-sha1-hash-in-c.html
	sha1 sha;
	sha.process_bytes(content.c_str(), content.length());

	// bof... would prefer array...but the digest does not support it
	unsigned int hash[5];
	sha.get_digest(hash); // get 5 uint (32 bits -- that can be converted into 8 hex characters) that, combined, maked for the 40 characters
    // This is done by just transforming the uints into hexadecimal values // 


	std::stringstream stream;

	std::string result;
	// there is something missing here...but what?
	for (int i = 0; i < 5; ++i) 
    {
		stream << std::hex << hash[i]; 
	}
    result += stream.str();

	//---------------------------------------------------------------
	// poutine syntaxique pour cr�er une compression en zlib -- pas besoin de ca pour le TP
	// https://www.boost.org/doc/libs/1_71_0/libs/iostreams/doc/classes/zlib.html
	boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
	in.push(boost::iostreams::zlib_compressor());
	in.push(boost::make_iterator_range(content));
	std::string compressed;
	boost::iostreams::copy(in, boost::iostreams::back_inserter(compressed));


	//--------------------------------------------------------
	// filesystem
	const auto fileName = "testResultat.txt";

	auto path = boost::filesystem::current_path();	// ou sommes nous?

    // l'op�reteur "/" sert � concat�ner un chemin (path -- style boost) avec un chemin ou bien une chaine de caract�res
	const auto pathFolder = path / "folder";	// ajouter un fichier de la mani�re d�cid�e par la plateforme
													// comme ca, on aura jamais de probl�me de plateforme
	
	if (!boost::filesystem::exists(pathFolder))  // peut lancer une exception
	{
		// si le r�pertoire n'existe pas, on le cr�e
		boost::filesystem::create_directory(pathFolder); // exception possible
        
	}

	boost::system::error_code code;
	if (!boost::filesystem::exists(pathFolder, code)) // ne lance pas d'exception .. c'est attrap� par le code
	{
		if (code.failed()) // et ensuite, on v�rifie pour voir si le code est ok
		{
			std::cout << "Something bad happened but we didn't throw anything...so thats good :)" << std::endl;
		}
	}


	//---------------------------------------------------------
	// ofstream tout normal et gentil

    const auto outputFilePath = pathFolder / fileName;
    boost::filesystem::ofstream outputFile(outputFilePath);

    if (!outputFile || !outputFile.is_open())
    {
        std::cout << "Error file" << std::endl;
    }
    

    

	// on �crit la compression, deux sauts de ligne et le sha
	outputFile << compressed << std::endl << std::endl << result;

	// il faudrait valider l'�criture ici...

	outputFile.close(); // on aime etre propre alors on ferme le fichier
						// th�oriquement, le RAII devrait le faire pour nous

    

}
