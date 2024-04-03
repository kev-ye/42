import * as React from 'react';
import {useContext, useEffect, useState} from "react";
import {useNavigate, Link as RouterLink} from "react-router-dom";

import Avatar from '@mui/material/Avatar';
import Button from '@mui/material/Button';
import CssBaseline from '@mui/material/CssBaseline';
import TextField from '@mui/material/TextField';
import Link from '@mui/material/Link';
import Grid from '@mui/material/Grid';
import Box from '@mui/material/Box';
import Typography from '@mui/material/Typography';
import Container from '@mui/material/Container';
import { createTheme, ThemeProvider } from '@mui/material/styles';
import {AlertColor} from "@mui/material/Alert";

import {ApiAuth} from "../../global/global";
import {AlertContext, UserContext} from "../../utils/context";
import {getCurrentUser} from "../../utils/api";
import {TransitionAlert as Alert} from "../../components/alert";
import {FortyTwoIcon} from "../../components/logo";


// function: authenticate
const auth = async (data: any, f: Function) => {
  const url = `${ApiAuth}/signin`
  const res = await fetch(url, {
    method: 'post',
    body: JSON.stringify(data),
    headers: { "Content-Type": "application/json" }
  })

  if (res.status !== 200) return null
  else {
    const data = await res.json()

    localStorage.setItem('__access_token__', data.access_token)
    localStorage.setItem('__refresh_token__', data.refresh_token)

    const user = await getCurrentUser()
    f(user)
    return user
  }
}


// component: copyright
function Copyright(props: any) {
  return (
    <Typography variant="body2" color="text.secondary" align="center" {...props}>
      {'Copyright © '}
      <Link color="inherit" href="http://localhost:3000/">Matcha</Link>
      {' '}
      {new Date().getFullYear()}
      {'.'}
    </Typography>
  );
}

const theme = createTheme();

// component: sign in (main)
const SignIn = () => {
  // context
  const { setUser } = useContext(UserContext)
  const { alert, setAlert } = useContext(AlertContext)

  // state
  const [open, setOpen] = useState(false)
  const [type, setType] = useState<AlertColor>('error')

  // navigate
  const navigate = useNavigate()

  // sign in handle submit event
  const handleSubmit = async (event: React.FormEvent<HTMLFormElement>) => {
    event.preventDefault();

    const data = new FormData(event.currentTarget);
    const identity = {
      username: data.get('username'),
      password: data.get('password')
    }

    const user = await auth(identity, setUser)
    if (user === null || user === false) {
      setOpen(true)
      setType('error')
      setAlert('Username or Password invalid')
    }
    else {
      setAlert(`Welcome ${user.username} !`)
      navigate('/')
    }
  };

  // initialize alert msg if exist
  useEffect(() => {
    const include = ['success', 'logged out']

    if (alert && include.some(element => alert.includes(element))) {
      setOpen(true)
      setType('success')
    }
  }, [])

  // component content
  return (
    <ThemeProvider theme={theme}>
      <Alert type={type} msg={alert} open={open} f={setOpen} />
      <Container component="main" maxWidth="xs">
        <CssBaseline />
        <Box
          sx={{
            marginTop: 16,
            display: 'flex',
            flexDirection: 'column',
            alignItems: 'center',
          }}
        >
          <Avatar sx={{ m: 1, bgcolor: '#9fa8a3' }}>
            <FortyTwoIcon />
          </Avatar>
          <Typography component="h1" variant="h5">
            Sign in
          </Typography>
          <Box component="form" onSubmit={handleSubmit} noValidate sx={{ mt: 1 }}>
            <TextField
              margin="normal"
              required
              fullWidth
              id="username"
              label="Username"
              name="username"
              autoComplete="username"
              autoFocus
            />
            <TextField
              margin="normal"
              required
              fullWidth
              name="password"
              label="Password"
              type="password"
              id="password"
              autoComplete="current-password"
            />
            <Button
              type="submit"
              fullWidth
              variant="contained"
              sx={{
                mt: 3,
                mb: 2,
                bgcolor: '#9fa8a3',
                opacity: '0.8',
                '&:hover': { bgcolor: '#9fa8a3', opacity: '1' }
              }}
            >
              Sign In
            </Button>
            <Grid container>
              <Grid item xs>
                <Link href="#" variant="body2">
                  Forgot password?
                </Link>
              </Grid>
              <Grid item>
                <RouterLink to="/signup" style={{ color: '#1976d2', textDecoration: 'none' }}>
                  {"Don't have an account? Sign Up"}
                </RouterLink>
              </Grid>
            </Grid>
          </Box>
        </Box>
        <Copyright sx={{ mt: 8, mb: 4 }} />
      </Container>
    </ThemeProvider>
  );
}

export default SignIn
