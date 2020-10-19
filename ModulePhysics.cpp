#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "math.h"

#include "Box2D/Box2D/Box2D.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));

	// big static circle as "ground" in the middle of the screen
	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 1.5f;
	int diameter = SCREEN_WIDTH / 2;

	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(diameter) * 0.5f;

	b2FixtureDef fixture;
	fixture.shape = &shape;
	b->CreateFixture(&fixture);

	return true;
}

void ModulePhysics::CreateCircle(float x, float y, int r) {
	b2BodyDef body;
	body.type = b2_dynamicBody;
	float radius = PIXEL_TO_METERS(r);
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	b2Body* b = world->CreateBody(&body);
	b2CircleShape shape;
	shape.m_radius = radius;
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;
	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	pbody->width = pbody->height = radius;

	//return pbody;
}

void ModulePhysics::CreateRectangle(float x, float y, float hx, float hy) {
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	b2Body* b = world->CreateBody(&body);
	b2PolygonShape shape;
	shape.SetAsBox(hx, hy);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	b->CreateFixture(&fixture);
	// TODO 2: To have the box behave normally, set fixture's density to 1.0f
	fixture.density = 1.0f;
}

void ModulePhysics::CreateChain(float x, float y) {
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	b2Body* b = world->CreateBody(&body);
	b2ChainShape shape;
	b2Vec2 points[42] = {
		b2Vec2(PIXEL_TO_METERS(-141),  PIXEL_TO_METERS(3)),
		b2Vec2(PIXEL_TO_METERS(-143),  PIXEL_TO_METERS(60)),
		b2Vec2(PIXEL_TO_METERS(-149),  PIXEL_TO_METERS(64)),
		b2Vec2(PIXEL_TO_METERS(-148),  PIXEL_TO_METERS(70)),
		b2Vec2(PIXEL_TO_METERS(-155),  PIXEL_TO_METERS(82)),
		b2Vec2(PIXEL_TO_METERS(-153),  PIXEL_TO_METERS(92)),
		b2Vec2(PIXEL_TO_METERS(-150),  PIXEL_TO_METERS(101)),
		b2Vec2(PIXEL_TO_METERS(-148),  PIXEL_TO_METERS(108)),
		b2Vec2(PIXEL_TO_METERS(-149),  PIXEL_TO_METERS(117)),
		b2Vec2(PIXEL_TO_METERS(-153),  PIXEL_TO_METERS(130)),
		b2Vec2(PIXEL_TO_METERS(-145),  PIXEL_TO_METERS(138)),
		b2Vec2(PIXEL_TO_METERS(-130),  PIXEL_TO_METERS(141)),
		b2Vec2(PIXEL_TO_METERS(-115), PIXEL_TO_METERS(140)),
		b2Vec2(PIXEL_TO_METERS(-111), PIXEL_TO_METERS(146)),
		b2Vec2(PIXEL_TO_METERS(-103), PIXEL_TO_METERS(148)),
		b2Vec2(PIXEL_TO_METERS(-102), PIXEL_TO_METERS(159)),
		b2Vec2(PIXEL_TO_METERS(-89), PIXEL_TO_METERS(160)),
		b2Vec2(PIXEL_TO_METERS(-77), PIXEL_TO_METERS(157)),
		b2Vec2(PIXEL_TO_METERS(-64), PIXEL_TO_METERS(151)),
		b2Vec2(PIXEL_TO_METERS(-65), PIXEL_TO_METERS(123)),
		b2Vec2(PIXEL_TO_METERS(-60), PIXEL_TO_METERS(122)),
		b2Vec2(PIXEL_TO_METERS(-57), PIXEL_TO_METERS(115)),
		b2Vec2(PIXEL_TO_METERS(-58), PIXEL_TO_METERS(108)),
		b2Vec2(PIXEL_TO_METERS(-64), PIXEL_TO_METERS(106)),
		b2Vec2(PIXEL_TO_METERS(-59), PIXEL_TO_METERS(75)),
		b2Vec2(PIXEL_TO_METERS(-48), PIXEL_TO_METERS(18)),
		b2Vec2(PIXEL_TO_METERS(-57), PIXEL_TO_METERS(22)),
		b2Vec2(PIXEL_TO_METERS(-60), PIXEL_TO_METERS(12)),
		b2Vec2(PIXEL_TO_METERS(-68), PIXEL_TO_METERS(18)),
		b2Vec2(PIXEL_TO_METERS(-69), PIXEL_TO_METERS(6)),
		b2Vec2(PIXEL_TO_METERS(-77), PIXEL_TO_METERS(16)),
		b2Vec2(PIXEL_TO_METERS(-82), PIXEL_TO_METERS(6)),
		b2Vec2(PIXEL_TO_METERS(-89), PIXEL_TO_METERS(14)),
		b2Vec2(PIXEL_TO_METERS(-92), PIXEL_TO_METERS(3)),
		b2Vec2(PIXEL_TO_METERS(-100), PIXEL_TO_METERS(12)),
		b2Vec2(PIXEL_TO_METERS(-104), PIXEL_TO_METERS(3)),
		b2Vec2(PIXEL_TO_METERS(-110), PIXEL_TO_METERS(11)),
		b2Vec2(PIXEL_TO_METERS(-117), PIXEL_TO_METERS(2)),
		b2Vec2(PIXEL_TO_METERS(-123), PIXEL_TO_METERS(13)),
		b2Vec2(PIXEL_TO_METERS(-128), PIXEL_TO_METERS(2)),
		b2Vec2(PIXEL_TO_METERS(-132), PIXEL_TO_METERS(13)),
		b2Vec2(PIXEL_TO_METERS(-141), PIXEL_TO_METERS(4))
	};

	shape.CreateLoop(points, 42);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	b->CreateFixture(&fixture);
	fixture.density = 1.0f;
}

// 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->GetVertexCount();
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
				}
				break;
			}
		}
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

void PhysBody::GetPosition(int& x, int& y)const {
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - width;
	y = METERS_TO_PIXELS(pos.y) - height;
}

float PhysBody::GetRotation()const {
	return RADTODEG * body->GetAngle();
}


 