class DriverInterface{
    public:
        DriverInterface();
        ~DriverInterface();
        void write_matrix(unsigned char matrix[30][3], unsigned int size);
    private:
        int fd;
};
