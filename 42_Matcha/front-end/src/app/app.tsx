import * as React from 'react';
import {useContext, useEffect, useState} from "react";
import {useNavigate} from 'react-router-dom'

import styled from "styled-components";

import Button from '@mui/material/Button';
import ButtonGroup from '@mui/material/ButtonGroup';
import Box from '@mui/material/Box';

import {AlertContext, UserContext} from "../utils/context";
import {TransitionAlert} from "../components/alert";

const Wrapper = styled.div`
  height: 100vh;
	position: relative;
`

const ContentWrapper = styled.div`
	margin: 0;
  position: absolute;
  top: 50%;
  left: 50%;
  -ms-transform: translate(-50%, -50%);
  transform: translate(-50%, -50%);
`

const VariantButtonGroup = () => {
	const navigate = useNavigate()

  return (
    <Box
      sx={{
        display: 'flex',
        flexDirection: 'column',
        alignItems: 'center',
        '& > *': {
					m: 1,
				},
      }}
    >
      <ButtonGroup
				sx={{ height: 100, backgroundColor: '#9fa8a3' }}
				variant="text"
				aria-label="button group"
				size='large'
			>
				<Button
					sx={{ width: '50vw', color: 'white' }}
					onClick={() => navigate('/matcha')}
				>Matcha</Button>
        <Button
					sx={{ width: '50vw', color: 'white' }}
					onClick={() => navigate('/finda')}
				>Finda</Button>
      </ButtonGroup>
    </Box>
  );
}

const App = () => {
	const { alert } = useContext(AlertContext)
	const { user, setUser } = useContext(UserContext)
	const [open, setOpen] = useState(
		!('firstTimeLogIn' in user) && alert !== null
	)

	useEffect(() => {
		if (!('firstTimeLogIn' in user)) {
			setUser((prev: any) => ({
				...prev,
				firstTimeLogIn: true
			}))
		}
		// eslint-disable-next-line react-hooks/exhaustive-deps
	}, [])

	return (
		<div>
			<TransitionAlert type="success" msg={alert} open={open} f={setOpen}/>
				 <Wrapper>
					 <ContentWrapper>
							<VariantButtonGroup />
						</ContentWrapper>
				 </Wrapper>
		</div>
	)
}

export default App