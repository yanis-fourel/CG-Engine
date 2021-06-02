#pragma once

namespace CG {

/*
	Entity with this component will be deleted after this tick, before application rendering
*/
struct ToDelete {
	bool dummy; // Otherwise it is treated as void and causes problem
};

}
