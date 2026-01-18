from django import forms


class LogForm(forms.Form):
    text = forms.CharField(label='', max_length=200, widget=forms.TextInput(attrs={'placeholder': 'Enter text'}))
