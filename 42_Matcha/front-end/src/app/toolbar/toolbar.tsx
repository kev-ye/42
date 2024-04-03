import * as React from "react";

import {UserContext} from "../../utils/context";
import NavLoggedOut from "./navLoggedOut";
import NavLoggedIn from "./navLoggedIn";

const ToolBar = () => {
	const { user } = React.useContext(UserContext)

	return user === null ? <NavLoggedOut /> : <NavLoggedIn />
}

export default ToolBar