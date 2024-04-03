import * as React from "react";
import {useContext} from "react";
import {useNavigate} from "react-router-dom";

import AppBar from '@mui/material/AppBar';
import Box from '@mui/material/Box';
import Toolbar from '@mui/material/Toolbar';
import IconButton from '@mui/material/IconButton';
import Typography from '@mui/material/Typography';
import Badge from '@mui/material/Badge';
import MenuItem from '@mui/material/MenuItem';
import Menu from '@mui/material/Menu';
import AccountCircle from '@mui/icons-material/AccountCircle';
import MailIcon from '@mui/icons-material/Mail';
import NotificationsIcon from '@mui/icons-material/Notifications';
import MoreIcon from '@mui/icons-material/MoreVert';
import SettingsIcon from '@mui/icons-material/Settings';
import LogoutIcon from '@mui/icons-material/Logout';
import HomeIcon from '@mui/icons-material/Home';

import {AlertContext, UserContext} from "../../utils/context";
import {FortyTwoIcon} from "../../components/logo";

const NavLoggedIn = () => {
  // context
  const {user, setUser} = useContext(UserContext)
  const {setAlert} = useContext(AlertContext)

  // mobile mode state
  const [mobileMoreAnchorEl, setMobileMoreAnchorEl] = React.useState<null | HTMLElement>(null);
  const isMobileMenuOpen = Boolean(mobileMoreAnchorEl);

  // navigate
  const navigate = useNavigate()

  // mobile mode event
  const handleMobileMenuOpen = (event: React.MouseEvent<HTMLElement>) => {
    setMobileMoreAnchorEl(event.currentTarget);
  };
  const handleMobileMenuClose = () => {
    setMobileMoreAnchorEl(null);
  };

  // event
  const signOut = () => {
    localStorage.clear()
    setAlert(`User ${user.username} logged out!`)
    setUser(null)
    navigate('/')
  }

  const toIndex = (event: React.MouseEvent<HTMLElement>) => {
    event.preventDefault()
    navigate('/')
  }

  // component mobile mode
  const mobileMenuId = 'primary-account-menu-mobile';
  const renderMobileMenu = (
    <Menu
      anchorEl={mobileMoreAnchorEl}
      anchorOrigin={{
        vertical: 'top',
        horizontal: 'right',
      }}
      id={mobileMenuId}
      keepMounted
      transformOrigin={{
        vertical: 'top',
        horizontal: 'right',
      }}
      open={isMobileMenuOpen}
      onClose={handleMobileMenuClose}
    >
      <MenuItem onClick={() => navigate('/')}>
        <IconButton size="large" aria-label="home" color="inherit" >
          <HomeIcon />
        </IconButton>
        <p>Home</p>
      </MenuItem>
      <MenuItem onClick={() => navigate('/profile')}>
        <IconButton size="large" aria-label="account of current user" color="inherit">
          <AccountCircle />
        </IconButton>
        <p>Profile</p>
      </MenuItem>
      <MenuItem onClick={() => navigate('/chat')}>
        <IconButton size="large" aria-label="show new mails" color="inherit">
          <Badge badgeContent={1} color="error"> {/* number of notification */}
            <MailIcon />
          </Badge>
        </IconButton>
        <p>Messages</p>
      </MenuItem>
      <MenuItem onClick={() => navigate('/collection')}>
        <IconButton size="large" aria-label="show new notifications" color="inherit">
          <Badge badgeContent={1} color="error"> {/* number of notification */}
            <NotificationsIcon />
          </Badge>
        </IconButton>
        <p>Notifications</p>
      </MenuItem>
      <MenuItem onClick={() => navigate('/setting')}>
        <IconButton size="large" aria-label="setting" color="inherit">
          <SettingsIcon />
        </IconButton>
        <p>Setting</p>
      </MenuItem>
      <MenuItem onClick={signOut}>
        <IconButton size="large" aria-label="signout" color="inherit">
          <LogoutIcon />
        </IconButton>
        <p>Logout</p>
      </MenuItem>
    </Menu>
  );

  // main component
  return (
    <Box sx={{ flexGrow: 1, position: 'absolute' }}>
      <AppBar>
        <Toolbar sx={{ backgroundColor: '#c5d5cb' }}>
          <FortyTwoIcon sx={{ mr: 2 }} onClick={toIndex} cursor="pointer"/>
          <Typography
            variant="h6"
            noWrap
            component="a"
            href="/"
            sx={{ display: { xs: 'none', sm: 'block' }, color: 'inherit', textDecoration: 'none' }}
            onClick={toIndex}
          >
            Matcha
          </Typography>

          <Box sx={{ flexGrow: 1 }} />
          <Box sx={{ display: { xs: 'none', md: 'flex' } }}>
            <IconButton size="large" aria-label="home" color="inherit" onClick={() => navigate('/')}>
              <HomeIcon /> {/* Home button */}
            </IconButton>
            <IconButton size="large" aria-label="account of current user" color="inherit" onClick={() => navigate('/profile')}>
              <AccountCircle /> {/* profile button */}
            </IconButton>
            <IconButton size="large" aria-label="show new mails" color="inherit" onClick={() => navigate('/chat')}>
              <Badge badgeContent={1} color="error"> {/* number of notification */}
                <MailIcon /> {/* mail button */}
              </Badge>
            </IconButton>
            <IconButton size="large" aria-label="show new notifications" color="inherit" onClick={() => navigate('/collection')}>
              <Badge badgeContent={1} color="error"> {/* number of notification */}
                <NotificationsIcon /> {/* notification button */}
              </Badge>
            </IconButton>
            <IconButton size="large" aria-label="setting" color="inherit" onClick={() => navigate('/setting')}>
              <SettingsIcon /> {/* setting button */}
            </IconButton>
            <IconButton size="large" aria-label="signout" color="inherit" onClick={signOut}>
              <LogoutIcon /> {/* logout button */}
            </IconButton>
          </Box>
          <Box sx={{ display: { xs: 'flex', md: 'none' } }}>
            <IconButton
              size="large"
              aria-label="show more"
              aria-controls={mobileMenuId}
              aria-haspopup="true"
              onClick={handleMobileMenuOpen}
              color="inherit"
            >
              <MoreIcon /> {/* mobile mode: open button */}
            </IconButton>
          </Box>
        </Toolbar>
      </AppBar>
      {renderMobileMenu} {/* mobile mode: content */}
    </Box>
  );
}

export default NavLoggedIn