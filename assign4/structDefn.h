/* Contact struct */
#ifndef STRUCT_H
#define STRUCT_H

typedef struct contact {
    unsigned long phoneNumber;
    long firstNamePosn;
    long lastNamePosn;
    long companyNamePosn;
    long emailPosn;
    long next;
} contact;

#endif
