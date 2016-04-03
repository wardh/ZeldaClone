#pragma once

#include "DL_Debug.h"

namespace CommonUtilities
{
	enum class eEvent
	{
		//Input Events ------------------------------------------
		INPUT_EVENTS,
		MOUSE_INPUT_EVENT,
		MOUSE_MOVE_EVENT,
		MOUSE_SCROLL_EVENT,
		KEYBOARD_INPUT_EVENT,
		KEYBOARD_STATE_EVENT,
		CONTROLLER_BUTTON_INPUT,
		CONTROLLER_ANALOGUE_INPUT,
		PLAYER_INPUT_ENABLED,
		//-------------------------------------------------------

		//Other events ------------------------------------------
		FUNCTION,
		SET_FLAG,
		IF_EVENT,
		MULTI_EVENT,
		TIMED_EVENT,
		QUIT,
		ERROR_,
		DEBUG_MODE,
		IS_LOADING,
		VIBRATE_CONTROLLER,
		CLEAR_PLAYER_GUI,
		SET_AFFECTED_BY_FOW,

		//Menu Events
		IN_GAME_STATE,

		//State Events
		NO_SCENE_HANDLE,
		REMOVE_CHILD_STATE,
		REMOVE_MAIN_STATE,

		//-------------------------------------------------------

		//Renderer Events ------------------------------------------
		RESIZE,
		NEW_FRAME,
		TOGGLE_SHADOWS,
		TEXT_ON_TEXTURE,
		SET_TEXTURE,
		RENDER_OBJECTIVE_TEXT,
		FADE_IN,
		FADE_OUT,
		INIT_INSTANCE,
		CHANGE_ALBEDO_EVENT,
		//-------------------------------------------------------
		// Game--------------------------------------
		START_SCENE,
		PAUSE,
		RESUME,
		TAKE_DAMAGE,
		HEAL,
		BLINK_MODEL,
		ADD_DAMAGE_VELOCITY,
		SPAWN_DAMAGE_CIRCLE,
		SWING_WEAPON,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_UP,
		MOVE_DOWN,
		ACTOR_DIRECTION,
		CHANGE_SPRITE,
		CHANGE_ANIMATION,
		COLLISION_BOX_COMPONENT,
		BULLET_COLLIDED,
		GIVE_PLAYER_EXPERIENCE,
		LOCK_MOVEMENT_COMPONENT,
		//-------------------------------------------------------

		//InternalEvents-----------------------------------------

		//-------------------------------------------------------


		MY_SIZE // Always last do not remove!
	};

	enum class eToolEvents
	{
		SPAWN_ENEMY_WITHIN_AREA,
		SET_FLAG,
		START_SCENE,
		QUIT,
		PLAY_SUBTITLE,
		REMOVE_MAIN_STATE,
		REMOVE_CHILD_STATE,
		MAX_SIZE
	};
	
}

namespace CU = CommonUtilities;