// This class are parts of William J Francis' SMBIOS Peek utility.
// source: https://www.codeproject.com/Articles/24730/SMBIOS-Peek-2

#pragma once

#define _UNICODE
#define MAX_DATA 0xFA00       // 64K
#define MAX_STRING 0x3E8      // 1K
#define MAX_STRING_TABLE 0x19 // 25
#define MEM_SIZE_MASK 0x07FFF

#include <windows.h>
#include <wbemcli.h>
#include <objbase.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <Tchar.h>
#include <stdio.h>
#include <string>

namespace smbios
{

    struct raw_smbios_data
    {
        unsigned char smbios_major_version;
        unsigned char smbios_minor_version;
        unsigned int length;
        unsigned char smbios_table_data[MAX_DATA];
    };

    struct required
    {
        unsigned char type;
        unsigned char length;
        unsigned char handle;
    };

    struct memory_device_type
    {
        required header;
        unsigned short physical_memory_array_handle;
        unsigned short memory_error_information_handle;
        unsigned short total_width;
        unsigned short data_width;
        unsigned short size;
        unsigned char form_factor;
        unsigned char device_set;
        _TCHAR device_locator[MAX_STRING * sizeof(_TCHAR)];
        _TCHAR bank[MAX_STRING * sizeof(_TCHAR)];
        unsigned char memory_type;
        unsigned short type_detail;
        unsigned short speed;
        _TCHAR manufactuer[MAX_STRING * sizeof(_TCHAR)];
        _TCHAR serial_number[MAX_STRING * sizeof(_TCHAR)];
        _TCHAR asset_tag[MAX_STRING * sizeof(_TCHAR)];
        _TCHAR part_number[MAX_STRING * sizeof(_TCHAR)];
        unsigned char rank;
    };

    class MemoryInfo
    {
    private:
        raw_smbios_data raw_bios_data;

    public:
        MemoryInfo();
        ~MemoryInfo();
        std::string get_memory_info();

    private:
        int get_unformatted_section_length(int index);
        int get_formatted_section_length(int index);
        bool return_next_table_of_type(void *p_return_buffer, int *return_buffer_length, bool reset);
        void get_string_resource_for_id(int target_id, unsigned char *in_buf, _TCHAR *out_string);
    };

        MemoryInfo::MemoryInfo()
    {
        HRESULT h_result;
        BSTR resource = SysAllocString(L"ROOT\\WMI");
        BSTR services = SysAllocString(L"MSSMBios_RawSMBiosTables");
        BSTR version = SysAllocString(L"SmbiosMajorVersion");
        BSTR data = SysAllocString(L"SMBiosData");

        memset(raw_bios_data.smbios_table_data, 0, MAX_DATA);
        h_result = CoInitializeEx(0, COINIT_MULTITHREADED);

        if (h_result < 0)
        {
            throw std::runtime_error("Failed to CoInitializeEx.");
        }

        IWbemLocator *p_locator = 0;
        CLSID CLSID_WbemLocator = {0x4590F811, 0x1D3A, 0x11D0, {0x89, 0x1F, 0, 0xAA, 0, 0x4B, 0x2E, 0x24}};
        IID IID_IWbemLocator = {0xdc12a687, 0x737f, 0x11cf, 0x88, 0x4d, 0x00, 0xaa, 0x00, 0x4b, 0x2e, 0x24};
        h_result = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID *)&p_locator);

        if (h_result < 0)
        {
            CoUninitialize();
            throw std::runtime_error("Failed to CoCreateInstance.");
        }

        IWbemServices *p_service = 0;
        h_result = p_locator->ConnectServer(resource, NULL, NULL, 0, NULL, 0, 0, &p_service);

        if (h_result < 0)
        {
            p_locator->Release();
            CoUninitialize();
            throw std::runtime_error("Failed to ConnectServer");
        }

        h_result = CoSetProxyBlanket(p_service, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
                                     RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);

        if (h_result < 0)
        {
            p_service->Release();
            p_locator->Release();
            CoUninitialize();
            throw std::runtime_error("Failed to CoSetProxyBlanket");
        }

        IEnumWbemClassObject *p_enumerator = NULL;
        h_result = p_service->CreateInstanceEnum(services, 0, NULL, &p_enumerator);

        if (h_result < 0)
        {
            p_service->Release();
            p_locator->Release();
            CoUninitialize();
            throw std::runtime_error("Failed to CreateInstanceEnum");
        }

        do
        {
            IWbemClassObject *p_instance = NULL;
            ULONG dw_count = NULL;

            h_result = p_enumerator->Next(WBEM_INFINITE, 1, &p_instance, &dw_count);
            if (h_result >= 0)
            {
                VARIANT variant_bios_data;
                VariantInit(&variant_bios_data);
                CIMTYPE type;

                h_result = p_instance->Get(version, 0, &variant_bios_data, &type, NULL);
                if (h_result < 0)
                {
                    VariantClear(&variant_bios_data);
                }
                else
                {
                    raw_bios_data.smbios_major_version = (unsigned char)variant_bios_data.iVal;
                    VariantInit(&variant_bios_data);
                    h_result = p_instance->Get(version, 0, &variant_bios_data, &type, NULL);
                    if (h_result < 0)
                    {
                        VariantClear(&variant_bios_data);
                    }
                    else
                    {
                        raw_bios_data.smbios_minor_version = (unsigned char)variant_bios_data.iVal;
                        VariantInit(&variant_bios_data);
                        h_result = p_instance->Get(data, 0, &variant_bios_data, &type, NULL);
                        if (h_result >= 0)
                        {
                            if ((VT_UI1 | VT_ARRAY) != variant_bios_data.vt)
                            {
                            }
                            else
                            {
                                SAFEARRAY *p_array = NULL;
                                p_array = V_ARRAY(&variant_bios_data);
                                unsigned char *p_data = (unsigned char *)p_array->pvData;

                                raw_bios_data.length = p_array->rgsabound[0].cElements;
                                if (raw_bios_data.length >= MAX_DATA)
                                {
                                    p_service->Release();
                                    p_locator->Release();
                                    CoUninitialize();
                                    throw std::overflow_error("buffer length is bigger than MAX_DATA");
                                }
                                memcpy(raw_bios_data.smbios_table_data, p_data, raw_bios_data.length);
                            }
                        }
                        VariantClear(&variant_bios_data);
                    }
                }
                break;
            }
        } while (h_result == WBEM_NO_ERROR);

        p_enumerator->Release();
        p_service->Release();
        p_locator->Release();

        CoUninitialize();

        SysFreeString(resource);
        SysFreeString(services);
        SysFreeString(version);
        SysFreeString(data);
    }

    int MemoryInfo::get_formatted_section_length(int index)
    {
        int type = raw_bios_data.smbios_table_data[index];
        if (type < 0 || type > 127)
        {
            return 0;
        }
        return raw_bios_data.smbios_table_data[index + 1];
    }

    int MemoryInfo::get_unformatted_section_length(int index)
    {
        int start_point = index;
        int unformatted_section_length = raw_bios_data.smbios_table_data[index + 1];
        index += unformatted_section_length;

        while (index < MAX_DATA)
        {
            if (raw_bios_data.smbios_table_data[index] == 0 && raw_bios_data.smbios_table_data[index + 1] == 0)
            {
                return index - unformatted_section_length + 2 - start_point;
            }

            index++;
        }

        return 0;
    }

    bool MemoryInfo::return_next_table_of_type(void *p_return_buffer, int *return_buffer_length, bool reset)
    {
        static int index;
        int formatted_section_length = 0;
        int unformatted_section_length = 0;
        int current_table_length = 0;

        if (reset)
        {
            index = 0;
        }

        while (true)
        {
            formatted_section_length = get_formatted_section_length(index);
            unformatted_section_length = get_unformatted_section_length(index);
            current_table_length = formatted_section_length + unformatted_section_length;

            if (raw_bios_data.smbios_table_data[index] == 17)
            {
                if (current_table_length >= *return_buffer_length)
                {
                    break;
                }

                memcpy(p_return_buffer, &(raw_bios_data.smbios_table_data[index]), current_table_length);
                *return_buffer_length = current_table_length;

                index += current_table_length;
                return true;
            }

            index += current_table_length;
            if (current_table_length == 0)
            {
                break;
            }
        }

        *return_buffer_length = 0;
        return false;
    }

    void MemoryInfo::get_string_resource_for_id(int target_id, unsigned char *in_buf, _TCHAR *out_string)
    {
        char array_of_string_entries[MAX_STRING_TABLE][MAX_STRING];
        int index = (int)*(in_buf + 1);
        int id = 0;
        int still_more_data = *(in_buf + index) + *(in_buf + index + 1);
        while (still_more_data)
        {
            int start_of_this_string = index;
            while (*(in_buf + index) != 0)
            {
                index++;
            }
            int len = index - start_of_this_string;
            index++;
            if (len > 0)
            {

                memcpy(array_of_string_entries[id], in_buf + start_of_this_string, len + 1);
            }
            id++;
            still_more_data = *(in_buf + index) + *(in_buf + index + 1);
        }

        target_id -= 1;

        if (target_id > id)
        {
            *(out_string) = NULL;
        }
        else
        {
            mbstowcs(out_string, array_of_string_entries[target_id], MAX_STRING * sizeof(_TCHAR));
        }
    }

    std::string MemoryInfo::get_memory_info()
    {
        std::stringstream sstream;

        bool result = true;
        int len = MAX_DATA;
        unsigned char buf[MAX_DATA];
        unsigned char *p_buf = buf;
        memset(buf, 0, MAX_DATA);

        int device_count = 0;
        memory_device_type mdt;
        bool found_a_device = false;

        std::string ram_name;
        int speed = -1;
        int num_of_sticks = 0;
        int total_size_mb = 0;

        do
        {
            memset(&mdt, 0, sizeof(memory_device_type));
            len = MAX_DATA;

            found_a_device = false;
            if (device_count < 1)
            {
                if (return_next_table_of_type(&buf, &len, true))
                {
                    found_a_device = true;
                    device_count++;
                }
            }
            else
            {
                if (return_next_table_of_type(&buf, &len, false))
                {
                    found_a_device = true;
                    device_count++;
                }
            }

            if (found_a_device)
            {
                memcpy(&mdt.header, p_buf, 4);
                memcpy(&mdt.physical_memory_array_handle, p_buf + 0x04, 2);
                memcpy(&mdt.memory_error_information_handle, p_buf + 0x06, 2);
                memcpy(&mdt.total_width, p_buf + 0x08, 2);
                memcpy(&mdt.data_width, p_buf + 0x0A, 2);
                memcpy(&mdt.size, p_buf + 0x0C, 2);
                mdt.form_factor = buf[0x0E];
                mdt.device_set = buf[0x0F];
                get_string_resource_for_id(buf[0x10], p_buf, mdt.device_locator);
                get_string_resource_for_id(buf[0x11], p_buf, mdt.bank);
                mdt.memory_type = buf[0x12];
                memcpy(&mdt.type_detail, p_buf + 0x13, 2);
                memcpy(&mdt.speed, p_buf + 0x15, 2);
                get_string_resource_for_id(buf[0x17], p_buf, mdt.manufactuer);
                get_string_resource_for_id(buf[0x18], p_buf, mdt.serial_number);
                get_string_resource_for_id(buf[0x19], p_buf, mdt.asset_tag);
                get_string_resource_for_id(buf[0x1A], p_buf, mdt.part_number);
                mdt.rank = buf[0x1B];

                if (mdt.size == 0)
                {
                    continue;
                }

                num_of_sticks++;
                total_size_mb += mdt.size;

                if (speed > 0)
                {
                    continue;
                }

                speed = mdt.speed;

                std::wstring manufactuer(mdt.manufactuer);
                ram_name += std::string(manufactuer.begin(), manufactuer.end());
                ram_name += "-";

                std::wstring part_number(mdt.part_number);
                int end = part_number.find_first_of(L'-');
                ram_name += std::string(part_number.begin(), part_number.begin() + end);
            }
        } while (found_a_device);

        sstream << ram_name.append(25 - ram_name.length(), ' ');
        sstream << std::fixed << std::setprecision(2) << (total_size_mb / 1024.0) << " GB\t";
        sstream << speed << "mhz";

        return sstream.str();
    }

    MemoryInfo::~MemoryInfo() = default;
}