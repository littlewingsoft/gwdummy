enum ERROR_CODE
{
	ERROR_NOT_FOUND_ROOM=8,					//방을 찾을 수 없습니다.
	ERROR_NOT_FOUND_USER,					//유저를 찾을 수 없습니다.
	ERROR_THE_ROOM_IS_FULL,					//방이 꽉 찼습니다.
	ERROR_CAN_NOT_ENTER_ROOM,				//방에 입장할수 없습니다.
	ERROR_NOT_ROOM_LEADER,					//방장이 아닙니다.
	ERROR_CAN_NOT_SUMMON_CREATURE,			//크리쳐를 소환할수 없 습니다.
	ERROR_CAN_NOT_CHG_DECK,					//덱을 변경 할 수 없습니다.
	ERROR_CAN_NOT_LEAVE_ROOM,				//방에 퇴장할 수 없습니다.
	ERROR_NOT_ENOUGH_EP,					//EP가 충분치 않습니다.
	ERROR_NOT_ENOUGH_MP,					//MP가 충분치 않습니다.
	ERROR_IS_NOT_ALLREADY,					//모두 준비 상태가 아닙니다.
	ERROR_CAN_NOT_ATTACK_PLAYER,			//플레이어를 공격할 수 없습니다.
	ERROR_CAN_NOT_FOUND_ATTACK_CREATURE,	//공격 크리쳐를 찾을 수 없습니다.
	ERROR_CAN_NOT_FOUND_ATTACKER,			//공격자를 찾을 수 없습니다.
	ERROR_CAN_NOT_FOUND_TARGET_USER,		//타겟 유저를 찾을 수 없습니다.
	ERROR_CAN_NOT_FOUND_TARGET_CREATURE,	//타겟 크리쳐를 찾을 수 없습니다.
	ERROR_TARGET_POS_IS_GRAVE,				//타겟 상태가 무덤에 있습니다.
	ERROR_SUMMON_WAIT_TIME,					//소환대기 시간입니다.
	ERROR_CREATURE_IS_LEFT,					//필드 크리쳐가 하나도 없어야 합니다.
	ERROR_EXIST_EQUIP_CREATURE,				//이미 장비 카드가 장착된 크리쳐 입니다.
	ERROR_TARGET_IS_NOT_CREATURE,			//타겟이 크리쳐가 아님니다.
	ERROR_TARGET_STATE_DEAD,				//타겟이 죽어 있습니다.
	ERROR_NOT_FOUND_CARD,					//카드를 찾을 수 없습니다.
	ERROR_NOT_FOUND_SKILL,					//스킬을 찾을 수 없습니다.
	ERROR_TARGET_IS_FRIEND,					//공격 대상이 아군입니다.
	ERROR_NOT_ENOUGH_INVEN_SPACE,			//인벤이 충분하지 않습니다.
	ERROR_ALREADY_SELECTED,					//이미 다 선택 했습니다.
	ERROR_UNABLE_TO_ATTACK_THE_TEAM,		//같은 팀은 공격 할 수 없습니다.
	//
	ERROR_CAN_NOT_ATTACK_1LINE,				//1진 크리쳐를 공격할 수 없습니다.
	//던전 파티 ui관련 error
	ERROR_NOT_ENOUGH_TOKEN,					//입장 가능 토큰이 충분치 않습니다.
	ERROR_NOT_PARTY_LEADER,					//파티 장이 아닙니다.
	ERROR_NOT_FOUND_PARTY,					//소속된 파티가 없습니다.
	ERROR_CAN_NOT_CREATE_PARTY,				//파티를 생성할 수 없습니다.
	ERROR_CAN_NOT_ENOUGH_LIFE_POINT			//라이프 포인트가 부족합니다.
	//

};