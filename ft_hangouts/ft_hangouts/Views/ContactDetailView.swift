import SwiftUI
import PhotosUI

struct ContactDetailView: View {
    @EnvironmentObject var appState: AppState
    @Environment(\.dismiss) var dismiss
    @State private var contact: Contact
    @State private var isEditing = false
    @State private var editedContact: Contact
    @State private var selectedPhoto: PhotosPickerItem?
    @State private var showingDeleteAlert = false
    @State private var showingMessages = false
    @State private var showingUserNotFoundAlert = false
    
    let onUpdate: () -> Void
    
    init(contact: Contact, onUpdate: @escaping () -> Void) {
        _contact = State(initialValue: contact)
        _editedContact = State(initialValue: contact)
        self.onUpdate = onUpdate
    }
    
    var body: some View {
        Form {
            Section {
                HStack {
                    Spacer()
                    // 编辑时显示editedContact的图片，这样选择后立即显示
                    if let photoData = (isEditing ? editedContact.photoData : contact.photoData), let uiImage = UIImage(data: photoData) {
                        if isEditing {
                            PhotosPicker(selection: $selectedPhoto, matching: .images) {
                                Image(uiImage: uiImage)
                                    .resizable()
                                    .scaledToFill()
                                    .frame(width: 120, height: 120)
                                    .clipShape(Circle())
                            }
                        } else {
                            Image(uiImage: uiImage)
                                .resizable()
                                .scaledToFill()
                                .frame(width: 120, height: 120)
                                .clipShape(Circle())
                        }
                    } else {
                        if isEditing {
                            PhotosPicker(selection: $selectedPhoto, matching: .images) {
                                Image(systemName: "person.circle.fill")
                                    .font(.system(size: 120))
                                    .foregroundColor(.gray)
                            }
                        } else {
                            Image(systemName: "person.circle.fill")
                                .font(.system(size: 120))
                                .foregroundColor(.gray)
                        }
                    }
                    Spacer()
                }
            }
            
            Section(header: Text("basic_info".localized)) {
                if isEditing {
                    TextField("name".localized, text: $editedContact.name)
                    TextField("phone_number".localized, text: $editedContact.phoneNumber)
                    TextField("email".localized, text: $editedContact.email)
                } else {
                    LabeledContent("name".localized, value: contact.name)
                    LabeledContent("phone_number".localized, value: contact.phoneNumber)
                    LabeledContent("email".localized, value: contact.email)
                }
            }
            
            Section(header: Text("additional_info".localized)) {
                if isEditing {
                    TextField("address".localized, text: $editedContact.address)
                    TextField("birthday".localized, text: $editedContact.birthday, prompt: Text("birthday_format".localized))
                } else {
                    LabeledContent("address".localized, value: contact.address)
                    LabeledContent("birthday".localized, value: contact.birthday)
                }
            }
            
            if !isEditing {
                Section {
                    Button(action: { checkAndOpenMessages() }) {
                        HStack {
                            Image(systemName: "message.fill")
                            Text("send_message".localized)
                        }
                    }
                    
                    Button(action: { callContact() }) {
                        HStack {
                            Image(systemName: "phone.fill")
                            Text("call_contact".localized)
                        }
                    }
                }
                
                Section {
                    Button(role: .destructive, action: { showingDeleteAlert = true }) {
                        Text("delete_contact".localized)
                    }
                }
            }
        }
        .navigationTitle(contact.name)
        .navigationBarTitleDisplayMode(.inline)
        .toolbar {
            ToolbarItem(placement: .navigationBarTrailing) {
                Button(isEditing ? "done".localized : "edit".localized) {
                    if isEditing {
                        saveChanges()
                    }
                    isEditing.toggle()
                }
            }
        }
        .alert("delete_contact_title".localized, isPresented: $showingDeleteAlert) {
            Button("cancel".localized, role: .cancel) { }
            Button("delete".localized, role: .destructive) {
                deleteContact()
            }
        } message: {
            Text("delete_contact_message".localized)
        }
        .alert("user_not_found".localized, isPresented: $showingUserNotFoundAlert) {
            Button("ok".localized, role: .cancel) { }
        } message: {
            Text("contact_user_not_registered".localized)
        }
        .sheet(isPresented: $showingMessages) {
            if let receiverUser = DatabaseManager.shared.getUser(phoneNumber: contact.phoneNumber) {
                ChatView(otherUser: receiverUser, otherUserName: contact.name)
            }
        }
        .onChange(of: selectedPhoto) { _, newValue in
            Task {
                if let data = try? await newValue?.loadTransferable(type: Data.self) {
                    editedContact.photoData = data
                }
            }
        }
    }
    
    private func saveChanges() {
        contact = editedContact
        DatabaseManager.shared.updateContact(contact)
        onUpdate()
    }
    
    private func deleteContact() {
        DatabaseManager.shared.deleteContact(contact)
        onUpdate()
        dismiss()
    }
    
    private func checkAndOpenMessages() {
        // Check if user exists before opening chat
        if DatabaseManager.shared.getUser(phoneNumber: contact.phoneNumber) != nil {
            showingMessages = true
        } else {
            showingUserNotFoundAlert = true
        }
    }
    
    private func callContact() {
        if let url = URL(string: "tel://\(contact.phoneNumber)") {
            UIApplication.shared.open(url)
        }
    }
}
