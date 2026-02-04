import SwiftUI
import PhotosUI

struct AddContactView: View {
    @EnvironmentObject var appState: AppState
    @Environment(\.dismiss) var dismiss
    
    @State private var name = ""
    @State private var phoneNumber = ""
    @State private var email = ""
    @State private var address = ""
    @State private var birthday = ""
    @State private var selectedPhoto: PhotosPickerItem?
    @State private var photoData: Data?
    
    let onSave: () -> Void
    
    var body: some View {
        NavigationView {
            Form {
                Section(header: Text("photo".localized)) {
                    HStack {
                        if let photoData = photoData, let uiImage = UIImage(data: photoData) {
                            Image(uiImage: uiImage)
                                .resizable()
                                .scaledToFill()
                                .frame(width: 80, height: 80)
                                .clipShape(Circle())
                        } else {
                            Image(systemName: "person.circle.fill")
                                .font(.system(size: 80))
                                .foregroundColor(.gray)
                        }
                        
                        PhotosPicker(selection: $selectedPhoto, matching: .images) {
                            Text("select_photo".localized)
                        }
                    }
                }
                
                Section(header: Text("basic_info".localized)) {
                    TextField("name".localized, text: $name)
                    TextField("phone_number".localized, text: $phoneNumber)
                        .keyboardType(.phonePad)
                    TextField("email".localized, text: $email)
                        .keyboardType(.emailAddress)
                }
                
                Section(header: Text("additional_info".localized)) {
                    TextField("address".localized, text: $address)
                    TextField("birthday".localized, text: $birthday, prompt: Text("birthday_format".localized))
                }
            }
            .navigationTitle("add_contact".localized)
            .navigationBarTitleDisplayMode(.inline)
            .toolbar {
                ToolbarItem(placement: .navigationBarLeading) {
                    Button("cancel".localized) {
                        dismiss()
                    }
                }
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button("save".localized) {
                        saveContact()
                    }
                    .disabled(name.isEmpty || phoneNumber.isEmpty)
                }
            }
            .onChange(of: selectedPhoto) { _, newValue in
                Task {
                    if let data = try? await newValue?.loadTransferable(type: Data.self) {
                        photoData = data
                    }
                }
            }
        }
    }
    
    private func saveContact() {
        guard let userId = appState.currentUser?.id else { return }
        
        let contact = Contact(
            userId: userId,
            name: name,
            phoneNumber: phoneNumber,
            email: email,
            address: address,
            birthday: birthday,
            notes: "",
            photoData: photoData,
            createdAt: Date()
        )
        
        _ = DatabaseManager.shared.createContact(contact)
        onSave()
        dismiss()
    }
}
