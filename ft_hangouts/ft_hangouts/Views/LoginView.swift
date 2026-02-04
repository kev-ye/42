import SwiftUI

struct LoginView: View {
    @EnvironmentObject var appState: AppState
    @State private var phoneNumber = ""
    @State private var showError = false
    
    var body: some View {
        NavigationView {
            VStack(spacing: 20) {
                Image(systemName: "phone.circle.fill")
                    .font(.system(size: 100))
                    .foregroundColor(.blue)
                    .padding()
                
                Text("login_title".localized)
                    .font(.title)
                    .bold()
                
                Text("login_subtitle".localized)
                    .font(.subheadline)
                    .foregroundColor(.gray)
                    .multilineTextAlignment(.center)
                    .padding(.horizontal)
                
                TextField("phone_number".localized, text: $phoneNumber)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                    .keyboardType(.phonePad)
                    .padding(.horizontal, 40)
                
                Button(action: login) {
                    Text("login_button".localized)
                        .frame(maxWidth: .infinity)
                        .padding()
                        .background(Color.blue)
                        .foregroundColor(.white)
                        .cornerRadius(10)
                }
                .padding(.horizontal, 40)
                .disabled(phoneNumber.isEmpty)
                
                if showError {
                    Text("login_error".localized)
                        .foregroundColor(.red)
                        .font(.caption)
                }
            }
            .padding()
            .navigationBarHidden(true)
        }
    }
    
    private func login() {
        guard !phoneNumber.isEmpty else {
            showError = true
            return
        }
        appState.setCurrentUser(phoneNumber: phoneNumber)
    }
}
