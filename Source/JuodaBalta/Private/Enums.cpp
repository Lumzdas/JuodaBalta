#include "Public/Enums.h"

namespace JuodaBalta {
	EPlayer InvertPlayer(EPlayer const Player) {
		return Player == EPlayer::White ? EPlayer::Black : EPlayer::White;
	}
}
