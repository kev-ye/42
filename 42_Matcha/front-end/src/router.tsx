import {useContext, useEffect, useMemo, useState} from "react";
import {
	BrowserRouter,
	Routes,
	Route,
} from 'react-router-dom';

import {AlertContext, UserContext} from "./utils/context";
import {setCurrentUser} from "./utils/api";

import ToolBar from "./app/toolbar/toolbar";
import Signin from "./app/signin/signin";
import Signup from "./app/signup/signup"
import App from "./app/app";
import Profile from "./app/profile/profile";
import Setting from "./app/setting/setting";
import Chat from "./app/chat/chat";
import Finda from "./app/finda/finda";
import Matcha from "./app/matcha/matcha";
import Collection from "./app/collection/collection";

// router stats (stat logged in and logged out)
const RouterStat = () => {
	const { user } = useContext(UserContext)

	return user === null
		? (
				<Routes>
					<Route path='/' element={<Signin />} />
					<Route path='/signin' element={<Signin />} />
					<Route path="/signup" element={<Signup />} />
					<Route path='*' element={<Signin />}/>
				</Routes>
		)
		: (
				<Routes>
					<Route path='/' element={<App />}/>
					<Route path='/index' element={<App />}/>
					<Route path='/collection' element={<Collection />}/>
					<Route path='/profile' element={<Profile />}/>
					<Route path='/setting' element={<Setting />}/>
					<Route path='/chat' element={<Chat />}/>
					<Route path='/matcha' element={<Matcha />}/>
					<Route path='/finda' element={<Finda />}/>
					<Route path='*' element={<App />}/>
				</Routes>
		)
}

const AppRouter = () => {
	const [user, setUser] = useState(null)
	const userValue = useMemo(() => ({user, setUser}), [user, setUser])

	const [alert, setAlert] = useState(null)
	const alertValue = useMemo(() => ({alert, setAlert}), [alert, setAlert])

	useEffect(() => {
		setCurrentUser(setUser).then()
	}, [])

	return (
			<BrowserRouter>
				<UserContext.Provider value={userValue}>
					<AlertContext.Provider value={alertValue}>
						<ToolBar />
						<RouterStat />
					</AlertContext.Provider>
				</UserContext.Provider>
			</BrowserRouter>
		)
}

export default AppRouter