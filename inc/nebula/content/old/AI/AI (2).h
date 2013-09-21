

#define AI_ANG_SPEED 5.0
#define AI_TARGET_RANGE 10.0
#define AI_MOVE_DISTANCE 5.0






class AIEngine
{
public:
	class AI
	{
	public:
		EntityMarine* parent;
		EntityMarine* target;

		double elapsed_time_rotate;

		int update_hold       ( GAME * g, MARINE * m, float elapsed_time_rotate );
		int update_hold_target( GAME * g, MARINE * m, float elapsed_time_rotate );
		int update_move       ( MARINE * m, OBJECTIVE<MARINE> * o, float elapsed_time_rotate );
		// core
		int shoot             ( GAME * g, MARINE * m );
		int rotate_ang        ( MARINE * m, float ang, float elapsed_time );
		int rotate_speed      ( MARINE * m, float relative_speed, float elapsed_time );
		int core_look_at      ( MARINE * m, Vector3 lookat, float elapsed_time, float &ang );
		int core_move_to      ( MARINE * m, Vector3 lookat );
	};

	ServerEngine* serverEngine;


	
	int update            ( std::vector<GAME*> game_pointer_vector );
	

}




int AIEngine::update( std::vector<GameEngine*> game )
{
    GAME * g;
    MARINE * m;
    OBJECTIVE<MARINE> * o;
    for ( int a = 0; a < game_pointer_vector.size(); a++ )
    {
        g = game_pointer_vector.at(a);
        for ( int b = 0; b < g->marines.size(); b++ )
        {
            m = g->marines.at(b);
            if ( ( m->control == CTRL_AI ) && ( m->health > 0 ) )
            {
                float elapsed_time_rotate = ((float)clock() - (float)m->last_rotate)/((float)CLOCKS_PER_SEC);
                m->last_rotate = clock();
                
                m->stop();
                
                for ( int c = 0; c < m->objective_pointer_vector.size(); c++ )
                {
                    o = m->objective_pointer_vector.at(c);
                    if ( o->data.state == OBJECTIVE_STATE_ACTIVE )
                    {
                        switch( o->data.type )
                        {
                        case OBJECTIVE_TYPE_HOLD:
                            if ( m->ai_target == NULL )
                            {
                                server_ai_update_hold( g, m, elapsed_time_rotate );
                            }
                            else
                            {
                                server_ai_update_hold_target( g, m, elapsed_time_rotate );
                            }
                            break;
                        case OBJECTIVE_TYPE_MOVE_AT_LEVEL:
                            
                            break;
                        case OBJECTIVE_TYPE_MOVE:
                            server_ai_update_move( m, o, elapsed_time_rotate );
                            break;
                        case OBJECTIVE_TYPE_FOLLOW:
                            break;
                        }
                        break;
                    }
                }
            }
        }
    }

	return 0;
}

int AIEngine::AI::update_hold       ()
{
    target = NULL;
	
    server_ai_rotate_speed( parent, AI_ANG_SPEED, elapsed_time_rotate );
    
    Vector3 v = parent->body.q * X;

    for ( int a = 0; a < parent->game->marines.size(); a++ )
    {
        target = g->marines.at(a);
        if ( ( target->health > 0 ) && ( target->address[0] != parent->address[0] ) )
        {
            Vector3 d = target->body.x - parent->body.x;
            
            float ang = v.angle(d);
			
            if ( ( ang < 45 ) && ( d.magnitude() < AI_TARGET_RANGE ) )
            {
                parent->ai_target = target;
                break;
            }
        }
    }
    return 0;
}
int AIEngine::AI::update_hold_target( GAME * g, MARINE * m, float elapsed_time_rotate )
{
    MARINE * target = m->ai_target;
    
    if ( target->health > 0 )
    {
        float ang;
        
        server_ai_core_look_at( m, target->body.x, elapsed_time_rotate, ang );
        
        if ( abs(ang) < 1 )
        {
            m->fire();
        }
    }
    else
    {
        m->ai_target = NULL;
    }
    return 0;
}
int AIEngine::AI::update_move       ( MARINE * m, OBJECTIVE<MARINE> * o, float elapsed_time_rotate )
{
    float ang;
    
    server_ai_core_look_at( m, Vector3(o->data.wp), elapsed_time_rotate, ang );
    
    server_ai_core_move_to( m, o->data.wp );
    
    return 0;
}
int AIEngine::AI::rotate_ang        ( MARINE * marine, float ang, float elapsed_time )
{
    if ( abs(ang) > (AI_ANG_SPEED*elapsed_time) )
    {
        if ( ang > 0 )
        {
            marine->body.rotate(Z,AI_ANG_SPEED*elapsed_time);
        }
        else
        {
            marine->body.rotate(Z,-1.0f*AI_ANG_SPEED*elapsed_time);
        }
    }
    else
    {
        marine->body.rotate(Z,ang);
    }
    return 0;
}
int AIEngine::AI::rotate_speed      ( MARINE * marine, float relative_speed, float elapsed_time )
{
    if ( relative_speed > 0 )
    {
        marine->body.rotate(Z,relative_speed*AI_ANG_SPEED*elapsed_time);
    }
    else
    {
        marine->body.rotate(Z,-1.0f*relative_speed*AI_ANG_SPEED*elapsed_time);
    }
    
    return 0;
}
int AIEngine::AI::shoot             ( GAME * g, MARINE * m )
{
	
	m->fire();
	
	//server_shot_handle_shot( m->body.q * X, m->body.x + m->body.eye_offset, g, m );
	
	return 0;
}
int AIEngine::AI::look_at           ( MARINE * m, Vector3 lookat, float elapsed_time, float &ang )
{
    Vector3 O = m->body.x + ( m->body.q.getConjugate() * m->body.eye_offset );
	Vector3 v = m->body.q * X;
	Vector3 d = lookat - O;
    ang = v.angle(d);
	
    server_ai_rotate_ang( m, ang, elapsed_time );
    
    return 0;
}
int AIEngine::AI::move_to           ( MARINE * m, Vector3 moveto )
{
    Vector3 d = moveto - m->body.x;
    
    if ( d.magnitude() > 0 )
    {
        d.normalize();
        
		m->move_v = m->body.q.getConjugate() * d;
    }
    return 0;
}

