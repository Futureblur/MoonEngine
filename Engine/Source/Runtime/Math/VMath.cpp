// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "VMath.h"

#include "Core/IO/Log.h"

namespace Iceblur
{
	void Resolution::ResolutionNullError()
	{
		ICE_WARN(Error::ETypes::A_MUST_BE_GREATER_THAN_ZERO, { "Resolution width or height" });
	}
}
