import * as React from "react";
import {Link as RouterLink, useNavigate} from "react-router-dom";

import AppBar from "@mui/material/AppBar";
import Container from "@mui/material/Container";
import Toolbar from "@mui/material/Toolbar";
import Typography from "@mui/material/Typography";
import Box from "@mui/material/Box";
import IconButton from "@mui/material/IconButton";
import MenuIcon from "@mui/icons-material/Menu";
import Menu from "@mui/material/Menu";
import MenuItem from "@mui/material/MenuItem";
import Button from "@mui/material/Button";
import {SvgIcon} from "@mui/material";
import {Si42} from 'react-icons/si';
import {FortyTwoIcon} from "../../components/logo";

const pages = [{
  name: 'Sign in',
  path: 'signin'
}, {
  name: 'Sign up',
  path: 'signup'
}]

const NavLoggedOut = () => {
  const [anchorElNav, setAnchorElNav] = React.useState<null | HTMLElement>(null);

  const handleOpenNavMenu = (event: React.MouseEvent<HTMLElement>) => {
    setAnchorElNav(event.currentTarget);
  };

  const handleCloseNavMenu = () => {
    setAnchorElNav(null);
  };

  const navigate = useNavigate()

  const toIndex = (event: React.MouseEvent<HTMLElement>) => {
    event.preventDefault()

    navigate('/')
  }

  return (
    <AppBar position="fixed">
      <Container sx={{ backgroundColor: '#c5d5cb' }} maxWidth="xl">
        <Toolbar disableGutters>
          <FortyTwoIcon sx={{ display: { xs: 'none', md: 'flex' }, mr: 1 }} cursor="pointer" onClick={toIndex} />
          <Typography
            variant="h6"
            noWrap
            component="a"
            href="/"
            sx={{
              mr: 2,
              display: { xs: 'none', md: 'flex' },
              fontFamily: 'monospace',
              fontWeight: 700,
              letterSpacing: '.3rem',
              color: 'inherit',
              textDecoration: 'none',
            }}
            onClick={toIndex}
          >
            Matcha
          </Typography>

          <Box sx={{ flexGrow: 1, display: { xs: 'flex', md: 'none' } }}>
            <IconButton
              size="large"
              aria-label="account of current user"
              aria-controls="menu-appbar"
              aria-haspopup="true"
              onClick={handleOpenNavMenu}
              color="inherit"
            >
              <MenuIcon />
            </IconButton>
            <Menu
              id="menu-appbar"
              anchorEl={anchorElNav}
              anchorOrigin={{
                vertical: 'bottom',
                horizontal: 'left',
              }}
              keepMounted
              transformOrigin={{
                vertical: 'top',
                horizontal: 'left',
              }}
              open={Boolean(anchorElNav)}
              onClose={handleCloseNavMenu}
              sx={{
                display: { xs: 'block', md: 'none' },
              }}
            >
              {pages.map((page) => (
                <RouterLink key={page.name} to={page.path} style={{ textDecoration: 'none', color: 'black' }}>
                  <MenuItem onClick={handleCloseNavMenu}>
                    <Typography textAlign="center">
                        {page.name}
                    </Typography>
                  </MenuItem>
                </RouterLink>
              ))}
            </Menu>
          </Box>

          <FortyTwoIcon sx={{ display: { xs: 'flex', md: 'none' }, mr: 1 }} cursor="pointer" onClick={toIndex} />
          <Typography
            variant="h5"
            noWrap
            component="a"
            href="/"
            sx={{
              mr: 2,
              display: { xs: 'flex', md: 'none' },
              flexGrow: 1,
              fontFamily: 'monospace',
              fontWeight: 700,
              letterSpacing: '.3rem',
              color: 'inherit',
              textDecoration: 'none',
            }}
            onClick={toIndex}
          >
            Matcha
          </Typography>

          <Box sx={{flexGrow: 1, display: { xs: 'none', md: 'flex' }, mr: 1}}>
            {pages.map((page) => (
              <RouterLink key={page.name} to={page.path} style={{ textDecoration: 'none', color: 'white' }}>
                <Button
                  onClick={handleCloseNavMenu}
                  sx={{ my: 2, color: 'white', display: 'block' }}
                >
                    {page.name}
                </Button>
              </RouterLink>
            ))}
          </Box>
        </Toolbar>
      </Container>
    </AppBar>
  );
};

export default NavLoggedOut