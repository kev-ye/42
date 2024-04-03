import * as React from 'react';
import {useContext, useState} from "react";
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

import {ApiAuth} from "../../global/global";
import {TransitionAlert as Alert} from "../../components/alert";
import {AlertContext} from "../../utils/context";
import {FortyTwoIcon} from "../../components/logo";

// function: subscription
const subscription = async (data: any) => {
  const url = `${ApiAuth}/signup`
  const res = await fetch(url, {
    method: 'post',
    body: JSON.stringify(data),
    headers: { "Content-Type": "application/json" }
  })

  if (res.status === 401) return res.json()
  return null
}

// component: copyright
const Copyright = (props: any) => {
  return (
    <Typography variant="body2" color="text.secondary" align="center" {...props}>
      {'Copyright © '}
      <Link color="inherit" href="http://localhost:3000/">
        Matcha
      </Link>{' '}
      {new Date().getFullYear()}
      {'.'}
    </Typography>
  );
}

const theme = createTheme();

// component: sign up (main)
const SignUp = () => {
  const navigate = useNavigate()
  const [open, setOpen] = useState(false)
  const { alert, setAlert } = useContext(AlertContext)

  const handleSubmit = async (event: React.FormEvent<HTMLFormElement>) => {
    event.preventDefault();

    const data = new FormData(event.currentTarget);
    const identity = {
      name: data.get('lastName'),
      fname: data.get('firstName'),
      username: data.get('username'),
      email: data.get('email'),
      password: data.get('password'),
    }

    const res = await subscription(identity)
    if (res) {
      setOpen(true)
      setAlert(res.msg)
    }
    else {
      setAlert(`Subscription success for ${identity.username}`)
      navigate('/signin')
    }
  };

  return (
    <ThemeProvider theme={theme}>
      <Alert type='error' msg={alert} open={open} f={setOpen} />
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
            Sign up
          </Typography>
          <Box component="form" noValidate onSubmit={handleSubmit} sx={{ mt: 3 }}>
            <Grid container spacing={2}>
              <Grid item xs={12} sm={6}>
                <TextField
                  autoComplete="given-name"
                  name="firstName"
                  required
                  fullWidth
                  id="firstName"
                  label="First Name"
                  autoFocus
                />
              </Grid>
              <Grid item xs={12} sm={6}>
                <TextField
                  required
                  fullWidth
                  id="lastName"
                  label="Last Name"
                  name="lastName"
                  autoComplete="family-name"
                />
              </Grid>
              <Grid item xs={12}>
                <TextField
                  required
                  fullWidth
                  id="username"
                  label="Username"
                  name="username"
                  autoComplete="username"
                />
              </Grid>
              <Grid item xs={12}>
                <TextField
                  required
                  fullWidth
                  id="email"
                  label="Email Address"
                  name="email"
                  autoComplete="email"
                />
              </Grid>
              <Grid item xs={12}>
                <TextField
                  required
                  fullWidth
                  name="password"
                  label="Password"
                  type="password"
                  id="password"
                  autoComplete="new-password"
                />
              </Grid>
            </Grid>
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
              Sign Up
            </Button>
            <Grid container justifyContent="flex-end">
              <Grid item>
                <RouterLink to="signin" style={{ color: '#1976d2', textDecoration: 'none' }}>
                  Already have an account? Sign in
                </RouterLink>
              </Grid>
            </Grid>
          </Box>
        </Box>
        <Copyright sx={{ mt: 5 }} />
      </Container>
    </ThemeProvider>
  );
}

export default SignUp