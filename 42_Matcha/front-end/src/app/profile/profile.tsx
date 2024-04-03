import * as React from 'react';
import {useContext, useState} from 'react';
import styled from "styled-components";

import Timeline from '@mui/lab/Timeline';
import TimelineItem from '@mui/lab/TimelineItem';
import TimelineSeparator from '@mui/lab/TimelineSeparator';
import TimelineConnector from '@mui/lab/TimelineConnector';
import TimelineContent from '@mui/lab/TimelineContent';
import TimelineOppositeContent from '@mui/lab/TimelineOppositeContent';
import TimelineDot from '@mui/lab/TimelineDot';
import EditIcon from '@mui/icons-material/Edit';
import Typography from '@mui/material/Typography';

import {UserContext} from "../../utils/context";
import TextCommonEditable from "./components/textCommonEditable";
import TextAreaCommonEditable from "./components/textAreaCommonEditable";
import RadioCommonEditable from "./components/radioCommonEditable";
import TagsCommonEditable from "./components/tagsCommonEditable";

const Wrapper = styled.div`
	margin-top: 64px
`

// main component
const CustomizedTimeline = () => {
  const { user, setUser } = useContext(UserContext)
	const [infoEditable, setInfoEditable] = useState<Array<any>>([
		{
			key: 'fname',
			keyRender: 'First name',
			value: user['fname'],
			stat: null,
			index: 0
		},
		{
			key: 'name',
			keyRender: 'Name',
			value: user['name'],
			stat: null,
			index: 1
		},
		{
			key: 'birthday',
			keyRender: 'Birthday',
			value: user['birthday'],
			stat: null,
			index: 2
		},
		{
			key: 'sex',
			keyRender: 'Sex',
			value: user['sex'],
			stat: null,
			index: 3
		},
		{
			key: 'bio',
			keyRender: 'Bio',
			value: user['bio'],
			stat: null,
			index: 4
		},
		{
			key: 'sex_o',
			keyRender: 'Sex orientation',
			value: user['sex_o'],
			stat: null,
			index: 5
		},
		{
			key: 'tag_l',
			keyRender: 'Tags',
			value: user['tag_l'],
			stat: null,
			index: 6
		},
	])

	const infoListEditable = {
		fname: (<TextCommonEditable
			info={infoEditable[0]}
			defaultValue={infoEditable[0].value}
			setE={setInfoEditable}
			setU={setUser}
		/>),
		name: (<TextCommonEditable
			info={infoEditable[1]}
			defaultValue={infoEditable[1].value}
			setE={setInfoEditable}
			setU={setUser}
		/>),
		birthday: user['birthday'],
		sex: (<RadioCommonEditable
			info={infoEditable[3]}
			defaultValue={infoEditable[3].value}
			setE={setInfoEditable}
			setU={setUser}
		/>),
		bio: (<TextAreaCommonEditable
			info={infoEditable[4]}
			defaultValue={infoEditable[4].value}
			setE={setInfoEditable}
			setU={setUser}
		/>),
		sex_o: (<RadioCommonEditable
			info={infoEditable[5]}
			defaultValue={infoEditable[5].value}
			setE={setInfoEditable}
			setU={setUser}
		/>),
		tag_l: (<TagsCommonEditable
			info={infoEditable[6]}
			defaultValue={infoEditable[6].value}
			setE={setInfoEditable}
			setU={setUser}
		/>)
	}

	const EditEvent = (editable: any, setE: React.Dispatch<any>, info: any) => {
		if (info.stat === 'editing') return

		setE((prev: any) => {
			prev[info.index].value = editable[info.key]
			prev[info.index].stat = 'editing'

			return [...prev]
		})
	}

	return (
    <Timeline>
      {infoEditable.map((info: any) => {
				return (
          <TimelineItem key={info.key}>
            <TimelineOppositeContent
              sx={{ m: 'auto 0' }}
              align="right"
              variant="body2"
              color="#9fa8a3"
            >
							{info.keyRender}
            </TimelineOppositeContent>
            <TimelineSeparator>
							<TimelineDot
								sx={{
									cursor: 'pointer',
									'&:hover': {opacity: '0.8'},
									'&:active': {bgcolor: '#9fa8a3'}
								}}
								onClick={() => EditEvent(infoListEditable, setInfoEditable, info)}
							>
								<EditIcon />
								</TimelineDot>
							<TimelineConnector />
            </TimelineSeparator>
            <TimelineContent sx={{ py: '24px', px: 2 }}>
              <Typography variant="h6" component="span" color='#9fa8a3' >
								{
									info.value === null
									? '?'
									: info.value
								}
              </Typography>
            </TimelineContent>
          </TimelineItem>
        )
      })}
    </Timeline>
  );
}

const Profile = () => {
	return (
		<Wrapper>
			<CustomizedTimeline />
		</Wrapper>
	)
}

export default Profile