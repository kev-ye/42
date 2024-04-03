import * as React from 'react';

import Box from '@mui/material/Box';
import Alert, {AlertColor} from '@mui/material/Alert';
import IconButton from '@mui/material/IconButton';
import Collapse from '@mui/material/Collapse';
import CloseIcon from '@mui/icons-material/Close';

export function TransitionAlert(props: { type: AlertColor, msg: string, open: boolean, f: Function }) {
  const { type, msg, open, f } = props

  return (
    <Box sx={{ width: '100%' }}>
      <Collapse in={open}>
        <Alert
          severity={type}
          action={
            <IconButton
              aria-label="close"
              color="inherit"
              size="small"
              onClick={() => {
                f(false);
              }}
            >
              <CloseIcon fontSize="inherit" />
            </IconButton>
          }
          sx={{ mb: 2, marginTop: '64px'}}
        >
          {msg}
        </Alert>
      </Collapse>
    </Box>
  );
}


