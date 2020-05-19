#ifndef _WRAPPER_H_
#define _WRAPPER_H_

#pragma once

/*
* @file : Wrapper.h
* @brief : Ce fichier d�finie les m�thodes utilis�es pour le Wrapper C++ -> C#
*/

#include "ImageClasse.h"
#include "ImageNdg.h"
#include "ImageCouleur.h"
#include "ImageDouble.h"
#include "LLD_OCR.h"

#include <cstring>

class Wrapper
{

	///////////////////////////////////////
	private:
	///////////////////////////////////////

	/*
	* @brief : Classe OCR du Low Level Driver (Traitement de l'image)
	*/
	LLD_OCR						*_LLD_OCR;		

	/*
	* @brief : Image pr�sente dans la fenetre de l'IHM
	*/
	CImageCouleur				*_IHMpicture;	

	/*
	* @brief : Nombre de champs de l'IHM (gestion de l'image)
	*/
	int							 _IHMnbData;	

	/*
	* @brief : Champs de l'IHM (gestion de l'image)
	*/
	std::vector<double>			 _IHMdata;											

	/*
	* @brief : Enleve d'image de l'IHM pr�sente dans le wrapper C#/C++
	*/
	void Wrapper_CleanImgIHM();		

	/*
	* @brief : Met � jour l'image de l'IHM pr�sente dans le wrapper C#/C++
	*/
	void Wrapper_ChangeImgIHM(int nbChamps, byte* data, int stride, int nbLig, int nbCol);		


	///////////////////////////////////////
	public:
	///////////////////////////////////////

	/*
	* @brief : Constructeur par d�faut du Wrapper
	*/
	_declspec(dllexport) Wrapper();	

	/*
	* @brief : Destructeur par d�faut
	*/
	_declspec(dllexport) ~Wrapper();				

	/*
	* @brief : Cette fonction acc�de au LLD afin de r�aliser l'OCR sur l'image d'�ntr�e
	* @param : (int) nbChamps : Nombre de champs dans l'image
	* @param : (byte) data : Donn�e pour chaque pixel
	* @param : (int) stride : Largeur d'une ligne, gestion multiple 32 bits
	* @param : (int) nbLig : Nombre de lignes de l'image
	* @param : (int) nbCol : Nombre de colonnes de l'image
	* @param : (int*) presets : Tableau de presets contenant les param�tres du traitement
	*/
	_declspec(dllexport) std::string Wrapper_getDOT(int nbChamps, byte* data, int stride, int nbLig, int nbCol );	// Analyse de l'image et retourne le DOT
};


extern "C" _declspec(dllexport) void LLD_getDOT(Wrapper *wrapper, char* dot, int nbChamps, byte* data, int stride, int nbLig, int nbCol)
{
	std::string dot_temp = wrapper->Wrapper_getDOT(nbChamps, data, stride, nbLig, nbCol);
}

extern "C" _declspec(dllexport) Wrapper *LLD_init()
{
	Wrapper *pLLD_wrapper = new Wrapper();
	return pLLD_wrapper;
}

#endif