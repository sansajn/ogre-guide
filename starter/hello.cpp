// OGRE 1.12 starter sample
#include <Ogre.h>
#include <OgreApplicationContext.h>

using namespace Ogre;
using namespace OgreBites;

class ogre_app
	: public ApplicationContext, public InputListener
{
public:
	ogre_app();
	~ogre_app() {}

private:
	void setup() override;
	bool keyPressed(KeyboardEvent const & evt) override;
};

ogre_app::ogre_app()
	: ApplicationContext{"OgreTutorialApp"}
{}

bool ogre_app::keyPressed(KeyboardEvent const & evt)
{
	if (evt.keysym.sym == SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
		return true;
	}
	else
		return false;  // key not processed
}

void ogre_app::setup()
{
	ApplicationContext::setup();
	addInputListener(this);  // register for input events

	SceneManager * scene = getRoot()->createSceneManager();
	scene->setAmbientLight(ColourValue{0.5, 0.5, 0.5});

	// register our scene with the RTSS
	RTShader::ShaderGenerator * shadergen = RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scene);

	SceneNode * root_nd = scene->getRootSceneNode();

	// without light we would just get a black screen
	Light * light = scene->createLight("MainLight");
	SceneNode * light_nd = root_nd->createChildSceneNode();
	light_nd->setPosition(20, 80, 50);
	light_nd->attachObject(light);

	// create camera so we can observe scene
	Camera * camera = scene->createCamera("MainCamera");
	camera->setNearClipDistance(5);  // specific to this sample
	camera->setAutoAspectRatio(true);
	SceneNode * camera_nd = root_nd->createChildSceneNode();
	camera_nd->setPosition(0, 0, 140);
	camera_nd->lookAt(Vector3{0, 0, -1}, Node::TS_PARENT);
	camera_nd->attachObject(camera);

	getRenderWindow()->addViewport(camera);  // render into the main window

	// finally something to render
	Entity * ent = scene->createEntity("ogrehead.mesh");
	SceneNode * node = root_nd->createChildSceneNode();
	node->attachObject(ent);
}

int main(int argc, char * argv[])
{
	ogre_app app;
	app.initApp();
	app.getRoot()->startRendering();
	app.closeApp();
	return 0;
}
