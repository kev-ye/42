from django.shortcuts import render, redirect
from django.conf import settings
from .forms import LogForm
from datetime import datetime
import os


def index(request):
    """Display form and history of submissions."""
    if request.method == 'POST':
        form = LogForm(request.POST)
        if form.is_valid():
            text = form.cleaned_data['text']
            timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
            
            # Write to log file
            log_path = settings.LOG_FILE_PATH
            os.makedirs(os.path.dirname(log_path), exist_ok=True)
            
            with open(log_path, 'a') as f:
                f.write(f'{timestamp} - {text}\n')
            
            return redirect('ex02_index')
    else:
        form = LogForm()
    
    # Read history from log file
    history = []
    log_path = settings.LOG_FILE_PATH
    if os.path.exists(log_path):
        with open(log_path, 'r') as f:
            history = f.readlines()
    
    return render(request, 'ex02/index.html', {'form': form, 'history': history})
