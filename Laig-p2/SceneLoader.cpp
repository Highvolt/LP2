#include <cstdlib>
#include "../tinyxml.h"


// Apontadores para os principais grupos
// declarados aqui como globais por conveni�ncia
// idealmente tudo seria inclu�do numa classe

TiXmlElement* initElement=NULL; 
TiXmlElement* matsElement=NULL;
TiXmlElement* textsElement=NULL;
TiXmlElement* leavesElement=NULL;
TiXmlElement* nodesElement=NULL;
TiXmlElement* graphElement=NULL;

//-------------------------------------------------------

TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val)
// Fun��o de pesquisa de um n� filho por compara��o de um atributo (normalmente um id) com um valor de refer�ncia
// numa vers�o mais alto n�vel seria utilizada uma express�o XPath
{
	TiXmlElement *child=parent->FirstChildElement();
	int found=0;

	while (child && !found)
		if (child->Attribute(attr) && strcmp(child->Attribute(attr),val)==0)
			found=1;
		else
			child=child->NextSiblingElement();

	return child;
}


//-------------------------------------------------------

void processGraphNode(TiXmlElement *parent, int nivel)
// fun��o recursiva de processamento do grafo
// ao encontrar um n�, aplica as defini��es declaradas e itera sobre os seus descendentes
// nota: se um n� A, declarado em 'Nodes' aparecer instanciado uma vez no grafo com descendentes B e C
// e posteriormente o n� A for novamente instanciado, a rela��o de descend�ncia com B e C n�o � impl�cita.
// Neste modelo o n� � s� uma transforma��o geom�trica ou de atributos, n�o uma defini��o de um sub-grafo 
// com v�rios n�s que pode ser reinstanciado
{
	TiXmlElement *child=parent->FirstChildElement();

	// cria um prefixo de espa�os para indenta��o, apenas para visualiza��o
	int prefixLen=nivel*2;
	char prefix[100];
	memset(prefix,' ',prefixLen);
	prefix[prefixLen]=0;

	while (child)
	{
		if (strcmp(child->Value(),"Node")==0)
		{
			// � um n�
			printf("%s Nodo do tipo '%s' com id '%s'\n",prefix, child->Value(), child->Attribute("id"));
			// acede aos dados do n� e aplica materiais, texturas, transforma��es
			// para aceder ao n�, existiriam v�rias alternativas
			// aqui implementa-se uma pesquisa b�sica
			TiXmlElement *node=findChildByAttribute(nodesElement,"id",child->Attribute("id"));

			if (node)
			{
				printf("%s     - Material id: '%s' \n", prefix, node->FirstChildElement("material")->Attribute("id"));
				printf("%s     - Texture id: '%s' \n", prefix, node->FirstChildElement("texture")->Attribute("id"));

				// repetir para outros detalhes do n�
			}


			// processa recursivamente os seus descendentes
			processGraphNode(child,nivel+1);
		}
		if (strcmp(child->Value(),"Leaf")==0)
		{
			// � folha
			printf("%s Folha do tipo '%s' com id '%s'\n",prefix, child->Value(), child->Attribute("id"));

			// acede aos dados declarados na sec��o Leaves
			TiXmlElement *leaf=findChildByAttribute(leavesElement,"id",child->Attribute("id"));

			if (leaf)
			{
				printf("%s     - tipo de folha: '%s' \n", prefix, leaf->Attribute("type"));
				// repetir para outros detalhes do n�
			}
			
			
			// e faz o render propriamente dito de acordo com o tipo de primitiva
			
		}

		child=child->NextSiblingElement();
	}

}

void loadScene(void)
{

	// Read string from file

	TiXmlDocument doc( "demograph.xml" );
	bool loadOkay = doc.LoadFile();

	if ( !loadOkay )
	{
		printf( "Could not load test file 'demotest.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
		exit( 1 );
	}

	initElement = doc.FirstChildElement( "Init" );
	matsElement = doc.FirstChildElement( "Materials" );
	textsElement =  doc.FirstChildElement( "Textures" );
	leavesElement =  doc.FirstChildElement( "Leaves" );
	nodesElement =  doc.FirstChildElement( "Nodes" );

	graphElement =  doc.FirstChildElement( "Graph" );


	// Inicializa��o
	// Um exemplo de um conjunto de n�s bem conhecidos e obrigat�rios

	if (initElement == NULL)
		printf("Bloco Init n�o encontrado\n");
	else
	{
		printf("Processing init:\n");
		// frustum: exemplo para n� com par�metros individuais
		TiXmlElement* frustumElement=initElement->FirstChildElement("frustum");
		if (frustumElement)
		{
			float near,far;

			if (frustumElement->QueryFloatAttribute("near",&near)==TIXML_SUCCESS && 
				frustumElement->QueryFloatAttribute("far",&far)==TIXML_SUCCESS
				)
				printf("  frustum attributes: %f %f\n", near, far);
			else
				printf("Error parsing frustum\n");
		}
		else
			printf("frustum not found\n");


		// translate: exemplo para um n� com um par�metro que aglutina v�rios floats
		TiXmlElement* translateElement=initElement->FirstChildElement("translate");
		if (translateElement)
		{
			char *valString=NULL;
			float x,y,z;

			valString=(char *) translateElement->Attribute("xyz");

			if(valString && sscanf(valString,"%f %f %f",&x, &y, &z)==3)
			{
				printf("  translate values (XYZ): %f %f %f\n", x, y, z);
			}
			else
				printf("Error parsing translate");
		}
		else
			printf("translate not found\n");		

		// repetir para cada uma das vari�veis
	}

	// Valida��o dos outros grupos seria feita aqui


	// render graph
	// itera��o recursiva
	processGraphNode(graphElement,0);

}
